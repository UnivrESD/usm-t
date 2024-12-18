// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top___024root.h"

VL_INLINE_OPT VlCoroutine Vtbench_top___024root___eval_initial__TOP__Vtiming__0(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_initial__TOP__Vtiming__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VdlySched.delay(5ULL, 
                                             nullptr, 
                                             "tb/testbench.sv", 
                                             12);
        vlSelfRef.tbench_top__DOT__clk = (1U & (~ (IData)(vlSelfRef.tbench_top__DOT__clk)));
    }
}

void Vtbench_top___024root___ico_sequent__TOP__0(Vtbench_top___024root* vlSelf);

void Vtbench_top___024root___eval_ico(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtbench_top___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vtbench_top___024root___eval_triggers__ico(Vtbench_top___024root* vlSelf);

bool Vtbench_top___024root___eval_phase__ico(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_phase__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtbench_top___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtbench_top___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtbench_top___024root___act_sequent__TOP__0(Vtbench_top___024root* vlSelf);

void Vtbench_top___024root___eval_act(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((4ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtbench_top___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vtbench_top___024root___nba_sequent__TOP__2(Vtbench_top___024root* vlSelf);

void Vtbench_top___024root___eval_nba(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((4ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtbench_top___024root___act_sequent__TOP__0(vlSelf);
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtbench_top___024root___ico_sequent__TOP__0(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtbench_top___024root___nba_sequent__TOP__2(vlSelf);
    }
}

void Vtbench_top___024root___timing_resume(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___timing_resume\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((8ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VdynSched.resume();
    }
    if ((4ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtbench_top___024root___eval_triggers__act(Vtbench_top___024root* vlSelf);

bool Vtbench_top___024root___eval_phase__act(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<4> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtbench_top___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtbench_top___024root___timing_resume(vlSelf);
        Vtbench_top___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtbench_top___024root___eval_phase__nba(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtbench_top___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtbench_top___024root___dump_triggers__ico(Vtbench_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtbench_top___024root___dump_triggers__nba(Vtbench_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtbench_top___024root___dump_triggers__act(Vtbench_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtbench_top___024root___eval(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vtbench_top___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("tb/testbench.sv", 6, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtbench_top___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtbench_top___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("tb/testbench.sv", 6, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vtbench_top___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("tb/testbench.sv", 6, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtbench_top___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtbench_top___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtbench_top___024root___eval_debug_assertions(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
