// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Keccak full round logic based on given input `Width`
// e.g. Width 800 requires 22 rounds
//
// This module has two phases:
// 1. Compute Theta, Rho, Pi steps.
// 2. Computes Chi and Iota steps.
//
// If masking is not enabled, the two phases are completed within a single
// clock cycle.
//
// If masking is enabled, the first phase (Phase1) completes in one cycle.
// The second phase then needs three clock cycles to complete:
// 1. In the first clock cycle, the first stage of Chi is computed for the
//    first lane halves.
// 2. In the second clock cycle, the module writes the updated first lane
//    halves to the state.
// 3. In the third clock cycle, the new second lane halves are written to
//    to the state.
//
// To deter SCA, we randomly decide which lane halves to process first on a
// per-round basis. We use additional randomness generated by the PRNG to take
// this decision (rand_aux_i). For more details, refer to the comments inside
// the FSM below.
//
// If masking is enabled, this implementation uses both randomness provided
// from an external PRNG as well as intermediate results for remasking the DOM
// multipliers below. Per clock cycle, 800b of pseudo-random data (PRD) are
// required. A carfully designed schedule ensures to only ever update the input
// data of the DOM multipliers when also providing fresh randomness and vice
// versa. Updating one without the other could lead to undesired SCA leakage.

`include "prim_assert.sv"

module keccak_round
  import prim_mubi_pkg::*;
#(
  parameter int Width = 1600, // b= {25, 50, 100, 200, 400, 800, 1600}

  // Derived
  localparam int W        = Width/25,
  localparam int L        = $clog2(W),
  localparam int MaxRound = 12 + 2*L,           // Keccak-f only
  localparam int RndW     = $clog2(MaxRound+1), // Representing up to MaxRound-1

  // Feed parameters
  parameter  int DInWidth = 64, // currently only 64bit supported
  localparam int DInEntry = Width / DInWidth,
  localparam int DInAddr  = $clog2(DInEntry),

  // Control parameters
  parameter  bit EnMasking    = 1'b0,  // Enable SCA hardening, requires Width >= 50
  parameter  bit ForceRandExt = 1'b0,  // 1: Always forward externally provided randomness.
                                       // 0: Switch between external randomness and internal
                                       //    intermediate state according to schedule.
  localparam int Share        = EnMasking ? 2 : 1
) (
  input clk_i,
  input rst_ni,

  // Message Feed
  input                valid_i,
  input [DInAddr-1:0]  addr_i,
  input [DInWidth-1:0] data_i [Share],
  output               ready_o,

  // In-process control
  input                    run_i,  // Pulse signal to initiates Keccak full round
  input                    rand_valid_i,
  input                    rand_early_i,
  input      [Width/2-1:0] rand_data_i,
  input                    rand_aux_i,
  output logic             rand_update_o,
  output logic             rand_consumed_o,

  output logic             complete_o, // Indicates full round is done

  // State out. This can be used as Digest
  output logic [Width-1:0] state_o [Share],

  // Life cycle
  input  lc_ctrl_pkg::lc_tx_t lc_escalate_en_i,

  // Errors:
  //  sparse_fsm_error: Checking if FSM state falls into unknown value
  output logic             sparse_fsm_error_o,
  //  round_count_error: prim_count checks round value consistency
  output logic             round_count_error_o,
  //  rst_storage_error: check if reset signal asserted out of the
  //                     permitted window
  output logic             rst_storage_error_o,

  input  prim_mubi_pkg::mubi4_t clear_i     // Clear internal state to '0
);

  import sha3_pkg::*;

  /////////////////////
  // Control signals //
  /////////////////////

  // Update storage register
  logic update_storage;

  // Reset the storage to 0 to initiate new Hash operation
  logic rst_storage;

  // XOR message into storage register
  // It only does based on the given DInWidth.
  // If DInWidth < Width, it takes multiple cycles to XOR all message
  logic xor_message;

  // Select Keccak_p datapath
  // 0: Select Phase1 (Theta -> Rho -> Pi)
  // 1: Select Phase2 (Chi -> Iota)
  // `phase_sel` needs to be asserted until the Chi stage is consumed,
  mubi4_t phase_sel;

  // DOM multiplier input/output mux control
  // 0: first compute upper, then lower lane halves
  // 1: first compute lower, then upper lane halves
  logic low_then_high_d, low_then_high_q;
  // 0: drive/select upper lane halves
  // 1: drive/select lower lane halves
  logic dom_out_low_d, dom_out_low_q;
  logic dom_in_low_d, dom_in_low_q;
  // 0: forward external randomness input
  // 1: forward partial intermediate results
  logic dom_in_rand_ext_d, dom_in_rand_ext_q;
  // 0: keep current intermediate results in pipeline registers
  // 1: latch new intermediate results into pipeline registers
  logic dom_update;

  // Increase/ Reset Round number
  logic inc_rnd_num;
  logic rst_rnd_num;

  // Round reaches end
  // This signal indicates the round reaches desired number, which is MaxRound -1.
  // MaxRound is dependant on the Width. In case of SHA3/SHAKE, MaxRound is 24.
  logic rnd_eq_end;

  // Complete of Keccak_f
  // State machine asserts `complete_d` when it reaches at the end of round and
  // operation (Phase3 if Masked). The stage, the storage still doesn't have
  // the valid states. So precisely it is not completed yet.
  // State generated `complete_d` is latched with the clock and creates a pulse
  // signal one cycle later. The signal is the indication of completion.
  //
  // Intentionally removed any intermediate step (so called StComplete) in order
  // to save a clock to proceeds next round.
  logic complete_d;

  //////////////////////
  // Datapath Signals //
  //////////////////////

  // Single round keccak output data
  logic [Width-1:0] keccak_out [Share];

  // Keccak Round indicator: range from 0 .. MaxRound
  logic [RndW-1:0] round;

  // Random value and valid signal used in Keccak_p
  logic               keccak_rand_update;
  logic               keccak_rand_consumed;
  logic [Width/2-1:0] keccak_rand_data;

  //////////////////////
  // Keccak Round FSM //
  //////////////////////

  // state inputs
  assign rnd_eq_end = (int'(round) == MaxRound - 1);

  keccak_st_e keccak_st, keccak_st_d;
  `PRIM_FLOP_SPARSE_FSM(u_state_regs, keccak_st_d, keccak_st, keccak_st_e, KeccakStIdle)

  // Next state logic and output logic
  // SEC_CM: FSM.SPARSE
  always_comb begin
    // Default values
    keccak_st_d = keccak_st;

    xor_message    = 1'b 0;
    update_storage = 1'b 0;
    rst_storage    = 1'b 0;

    inc_rnd_num = 1'b 0;
    rst_rnd_num = 1'b 0;

    keccak_rand_update   = 1'b 0;
    keccak_rand_consumed = 1'b 0;

    phase_sel = MuBi4False;
    low_then_high_d = low_then_high_q;
    dom_in_low_d = dom_in_low_q;
    dom_in_rand_ext_d = dom_in_rand_ext_q;
    dom_update = 1'b 0;

    complete_d = 1'b 0;

    sparse_fsm_error_o = 1'b 0;

    unique case (keccak_st)
      KeccakStIdle: begin
        if (valid_i) begin
          // State machine allows Sponge Absorbing only in Idle state.
          keccak_st_d = KeccakStIdle;

          xor_message    = 1'b 1;
          update_storage = 1'b 1;
        end else if (prim_mubi_pkg::mubi4_test_true_strict(clear_i)) begin
          // Opt1. State machine allows resetting the storage only in Idle
          // Opt2. storage resets regardless of states but clear_i
          // Both are added in the design at this time. Will choose the
          // direction later.
          keccak_st_d = KeccakStIdle;

          rst_storage = 1'b 1;
        end else if (EnMasking && run_i) begin
          // Masked version of Keccak handling
          keccak_st_d = KeccakStPhase1;

          // Drive DOM multiplier I/O mux signals for Phase 1.
          dom_in_low_d = low_then_high_q;
          dom_in_rand_ext_d = 1'b 0;
        end else if (!EnMasking && run_i) begin
          // Unmasked version of Keccak handling
          keccak_st_d = KeccakStActive;
        end else begin
          keccak_st_d = KeccakStIdle;
        end
      end

      KeccakStActive: begin
        // Run Keccak single round logic until it reaches MaxRound - 1
        update_storage = 1'b 1;

        if (rnd_eq_end) begin
          keccak_st_d = KeccakStIdle;

          rst_rnd_num = 1'b 1;
          complete_d  = 1'b 1;
        end else begin
          keccak_st_d = KeccakStActive;

          inc_rnd_num = 1'b 1;
        end
      end

      KeccakStPhase1: begin
        // Compute Theta, Rho, Pi - The DOM multipliers are not evaluated at
        // all: their inputs are driven by the first lane halves (same values
        // as in Phase2Cycle3 of the last round). Also, the intermediate
        // results we already had in Phase2Cycle3 didn't change.
        phase_sel = MuBi4False;
        dom_update = 1'b 0;

        // Only update the state and move on once we know the auxiliary
        // randomness required for Phase2 will be available in the next clock
        // cycle.
        //
        // It's important that the DOM multipliers inside keccak_2share are
        // presented the new state (updated with update_storage) at the same
        // time as the new randomness (updated with rand_update_o). Otherwise,
        // stale entropy is paired with fresh data or vice versa. This could
        // lead to undesired SCA leakage.
        if (rand_early_i || rand_valid_i) begin
          keccak_st_d = KeccakStPhase2Cycle1;
          update_storage = 1'b 1;
          keccak_rand_update = 1'b 1;

          // Update lane halves processing order for this round.
          low_then_high_d = rand_aux_i;

          // Drive DOM multiplier I/O mux signals for next phase.
          dom_in_low_d = low_then_high_d;
          dom_in_rand_ext_d = 1'b 1;
        end else begin
          keccak_st_d = KeccakStPhase1;
        end
      end

      KeccakStPhase2Cycle1: begin
        // Compute first stage of Chi for first lane halves using the DOM
        // multipliers. Use the fresh randomness provided by the PRNG for
        // remasking.
        phase_sel = MuBi4True;
        dom_update = 1'b 1;

        // Trigger randomness update for next cycle.
        // It's important that the DOM multipliers inside keccak_2share are
        // presented the second lane halves at the same time as the new
        // randomness (updated with rand_update_o). Otherwise, stale entropy
        // is paired with fresh data or vice versa. This could lead to
        // undesired SCA leakage.
        keccak_rand_update = 1'b 1;

        // Unconditionally move to next phase/cycle.
        keccak_st_d = KeccakStPhase2Cycle2;

        // Drive DOM multiplier I/O mux signals for next phase.
        dom_in_low_d = ~low_then_high_q;
        dom_in_rand_ext_d = 1'b 1;
      end

      KeccakStPhase2Cycle2: begin
        // Chi Stage 1 for second lane halves.
        // Chi Stage 2 and Iota for first lane halves.
        // Compute second stage of Chi and Iota for first lane halves.
        // Compute first stage of Chi for second lane halves. Use the fresh
        // randomness provided by the PRNG for remasking the DOM multipliers.
        phase_sel = MuBi4True;
        dom_update = 1'b 1;

        // Trigger randomness update for next cycle.
        // It's important that the DOM multipliers inside keccak_2share are
        // presented the updated state at the same as the new randomness
        // (updated with rand_update_o) - even if the DOM multipliers don't
        // update the pipeline registers in the next cycle. Otherwise, stale
        // entropy is paired with fresh data or vice versa. This could lead to
        // undesired SCA leakage.
        keccak_rand_update = 1'b 1;

        // Trigger auxiliary randomness update for next round. The rand_aux_i
        // signal is actually going to change in 2 clock cycles from now
        // (Phase1) based on the PRNG output in the next cycle (Phase2Cycle3)
        // in which the DOM multipliers don't update the pipeline registers.
        keccak_rand_consumed = 1'b 1;

        // Update first lane halves.
        update_storage = 1'b 1;

        // Unconditionally move to next phase/cycle.
        keccak_st_d = KeccakStPhase2Cycle3;

        // Drive DOM multiplier I/O mux signals for next phase.
        dom_in_low_d = low_then_high_q;
        dom_in_rand_ext_d = 1'b 0;
      end

      KeccakStPhase2Cycle3: begin
        // Compute second stage of Chi and Iota for second lane halves.
        // Feed again first lane halves to DOM multiplier inputs (now
        // the updated values become visible) together with intermediate
        // results of Phase2Cycle2. Don't update the register stage inside
        // the DOM multipliers.
        phase_sel = MuBi4True;
        dom_update = 1'b 0;

        // Update second lane halves.
        // We don't need fresh randomness for the next cycle as the DOM
        // multipliers inside keccak_2share will keep seeing the first
        // lane halves in the next cycle. If we updated the randomness,
        // old data got combined with frash randomness which is not
        // desirable as it could lead to SCA leakage.
        update_storage = 1'b 1;

        if (rnd_eq_end) begin
          // We're done.
          keccak_st_d = KeccakStIdle;

          rst_rnd_num    = 1'b 1;
          complete_d     = 1'b 1;
        end else begin
          // Continue to the next round.
          keccak_st_d = KeccakStPhase1;

          inc_rnd_num = 1'b 1;

          // Drive DOM multiplier I/O mux signals for next phase.
          dom_in_low_d = low_then_high_q;
          dom_in_rand_ext_d = 1'b 0;
        end
      end

      KeccakStError: begin
        keccak_st_d = KeccakStError;
      end

      KeccakStTerminalError: begin
        //this state is terminal
        keccak_st_d = keccak_st;
        sparse_fsm_error_o = 1'b 1;
      end

      default: begin
        keccak_st_d = KeccakStTerminalError;
        sparse_fsm_error_o = 1'b 1;
      end
    endcase

    // SEC_CM: FSM.GLOBAL_ESC, FSM.LOCAL_ESC
    // Unconditionally jump into the terminal error state
    // if the life cycle controller triggers an escalation.
    if (lc_ctrl_pkg::lc_tx_test_true_loose(lc_escalate_en_i)) begin
      keccak_st_d = KeccakStTerminalError;
    end
  end

  // When taking the lower lane halves in, the upper lane halves are output and
  // vice versa.
  assign dom_out_low_d = ~dom_in_low_d;

  if (EnMasking) begin : gen_regs_dom_ctrl
    always_ff @(posedge clk_i or negedge rst_ni) begin
      if (!rst_ni) begin
        low_then_high_q <= 1'b 0;
        dom_out_low_q <= 1'b 0;
        dom_in_low_q <= 1'b 0;
      end else begin
        low_then_high_q <= low_then_high_d;
        dom_out_low_q <= dom_out_low_d;
        dom_in_low_q <= dom_in_low_d;
      end
    end

    if (!ForceRandExt) begin : gen_reg_dom_in_rand_ext
      always_ff @(posedge clk_i or negedge rst_ni) begin
        if (!rst_ni) begin
          dom_in_rand_ext_q <= 1'b 0;
        end else begin
          dom_in_rand_ext_q <= dom_in_rand_ext_d;
        end
      end
    end else begin : gen_force_dom_in_rand_ext
      // Always forward the externally provided randomness.
      assign dom_in_rand_ext_q = 1'b 1;
      // Tie off unused signals.
      logic unused_dom_in_rand_ext;
      assign unused_dom_in_rand_ext = dom_in_rand_ext_d;
    end
  end else begin : gen_no_regs_dom_ctrl
    logic unused_dom_ctrl;
    assign unused_dom_ctrl =
        ^{low_then_high_d, dom_out_low_d, dom_in_low_d, dom_in_rand_ext_d};
    assign low_then_high_q = 1'b 0;
    assign dom_out_low_q = 1'b 0;
    assign dom_in_low_q = 1'b 0;
    assign dom_in_rand_ext_q = 1'b 0;
  end

  // Ready indicates the keccak_round is able to receive new message.
  // While keccak_round is processing the data, it blocks the new message to be
  // XORed into the current state.
  assign ready_o = (keccak_st == KeccakStIdle) ? 1'b 1 : 1'b 0;

  ////////////////////////////
  // Keccak state registers //
  ////////////////////////////

  // SEC_CM: LOGIC.INTEGRITY
  logic rst_n;
  prim_sec_anchor_buf #(
   .Width(1)
  ) u_prim_sec_anchor_buf (
    .in_i(rst_ni),
    .out_o(rst_n)
  );

  logic [Width-1:0] storage   [Share];
  logic [Width-1:0] storage_d [Share];
  always_ff @(posedge clk_i or negedge rst_n) begin
    if (!rst_n) begin
      storage <= '{default:'0};
    end else if (rst_storage) begin
      storage <= '{default:'0};
    end else if (update_storage) begin
      storage <= storage_d;
    end
  end

  assign state_o = storage;

  // Storage register input
  // The incoming message is XORed with the existing storage registers.
  // The logic can accept not a block size incoming message chunk but
  // the size defined in `DInWidth` parameter with its position.

  always_comb begin
    storage_d = keccak_out;
    if (xor_message) begin
      for (int j = 0 ; j < Share ; j++) begin
        for (int unsigned i = 0 ; i < DInEntry ; i++) begin
          // ICEBOX(#18029): handle If Width is not integer divisable by DInWidth
          // Currently it is not allowed to have partial write
          // Please see the Assertion `WidthDivisableByDInWidth_A`
          if (addr_i == i[DInAddr-1:0]) begin
            storage_d[j][i*DInWidth+:DInWidth] =
              storage[j][i*DInWidth+:DInWidth] ^ data_i[j];
          end else begin
            storage_d[j][i*DInWidth+:DInWidth] = storage[j][i*DInWidth+:DInWidth];
          end
        end // for i
      end // for j
    end // if xor_message
  end

  // Check the rst_storage integrity
  logic rst_storage_error;

  always_comb begin : chk_rst_storage
    rst_storage_error = 1'b 0;

    if (rst_storage) begin
      // FSM should be in KeccakStIdle and clear_i should be high
      if ((keccak_st != KeccakStIdle) ||
        prim_mubi_pkg::mubi4_test_false_loose(clear_i)) begin
        rst_storage_error = 1'b 1;
      end
    end
  end : chk_rst_storage

  assign rst_storage_error_o = rst_storage_error ;

  //////////////
  // Datapath //
  //////////////
  keccak_2share #(
    .Width(Width),
    .EnMasking(EnMasking),
    .ForceRandExt(ForceRandExt)
  ) u_keccak_p (
    .clk_i,
    .rst_ni,

    .lc_escalate_en_i,

    .rnd_i(round),

    .phase_sel_i      (phase_sel),
    .dom_out_low_i    (dom_out_low_q),
    .dom_in_low_i     (dom_in_low_q),
    .dom_in_rand_ext_i(dom_in_rand_ext_q),
    .dom_update_i     (dom_update),

    .rand_i(keccak_rand_data),

    .s_i(storage),
    .s_o(keccak_out)
  );

  // keccak entropy handling
  assign rand_update_o   = keccak_rand_update;
  assign rand_consumed_o = keccak_rand_consumed;

  assign keccak_rand_data = rand_data_i;

  // Round number
  // This primitive is used to place a hardened counter
  // SEC_CM: CTR.REDUN
  prim_count #(
    .Width(RndW)
  ) u_round_count (
    .clk_i,
    .rst_ni,
    .clr_i(rst_rnd_num),
    .set_i(1'b0),
    .set_cnt_i('0),
    .incr_en_i(inc_rnd_num),
    .decr_en_i(1'b0),
    .step_i(RndW'(1)),
    .commit_i(1'b1),
    .cnt_o(round),
    .cnt_after_commit_o(),
    .err_o(round_count_error_o)
  );

  // completion signal
  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      complete_o <= 1'b 0;
    end else begin
      complete_o <= complete_d;
    end
  end

  ////////////////
  // Assertions //
  ////////////////

  // Only allow `DInWidth` that `Width` is integer divisable by `DInWidth`
  `ASSERT_INIT(WidthDivisableByDInWidth_A, (Width % DInWidth) == 0)

  // If `run_i` triggerred, it shall complete
  //`ASSERT(RunResultComplete_A, run_i ##[MaxRound:] complete_o, clk_i, !rst_ni)

  // valid_i and run_i cannot be asserted at the same time
  `ASSUME(OneHot0ValidAndRun_A, $onehot0({valid_i, run_i}), clk_i, !rst_ni)

  // valid_i, run_i only asserted in Idle state
  `ASSUME(ValidRunAssertStIdle_A, valid_i || run_i |-> keccak_st == KeccakStIdle, clk_i, !rst_ni)

  // clear_i is assumed to be asserted in Idle state
  `ASSUME(ClearAssertStIdle_A,
    prim_mubi_pkg::mubi4_test_true_strict(clear_i)
     |-> keccak_st == KeccakStIdle, clk_i, !rst_ni)

  // EnMasking controls the valid states
  if (EnMasking) begin : gen_mask_st_chk
    `ASSERT(EnMaskingValidStates_A, keccak_st != KeccakStActive, clk_i, !rst_ni)
  end else begin : gen_unmask_st_chk
    `ASSERT(UnmaskValidStates_A, !(keccak_st
        inside {KeccakStPhase1, KeccakStPhase2Cycle1, KeccakStPhase2Cycle2, KeccakStPhase2Cycle3}),
        clk_i, !rst_ni)
  end
endmodule
