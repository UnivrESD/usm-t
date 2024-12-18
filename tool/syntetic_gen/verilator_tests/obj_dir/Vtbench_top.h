// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VTBENCH_TOP_H_
#define VERILATED_VTBENCH_TOP_H_  // guard

#include "verilated.h"

class Vtbench_top__Syms;
class Vtbench_top___024root;
class VerilatedVcdC;
class Vtbench_top___024unit;
class Vtbench_top___024unit__03a__03adriver__Vclpkg;
class Vtbench_top___024unit__03a__03aenvironment__Vclpkg;
class Vtbench_top___024unit__03a__03agenerator__Vclpkg;
class Vtbench_top___024unit__03a__03atransaction__Vclpkg;
class Vtbench_top_controller_intf;
class Vtbench_top_std;
class Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg;
class Vtbench_top_std__03a__03aprocess__Vclpkg;
class Vtbench_top_std__03a__03asemaphore__Vclpkg;
class Vtbench_top_test;
class Vtbench_top_test__03a__03amy_trans__Vclpkg;


// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) Vtbench_top VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vtbench_top__Syms* const vlSymsp;

  public:

    // CONSTEXPR CAPABILITIES
    // Verilated with --trace?
    static constexpr bool traceCapable = true;

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.
    Vtbench_top___024unit* const __PVT____024unit;
    Vtbench_top_std* const __PVT__std;
    Vtbench_top_controller_intf* const __PVT__tbench_top__DOT__intf;
    Vtbench_top_test* const __PVT__tbench_top__DOT__t1;
    Vtbench_top___024unit__03a__03atransaction__Vclpkg* const __024unit__03a__03atransaction__Vclpkg;
    Vtbench_top___024unit__03a__03agenerator__Vclpkg* const __024unit__03a__03agenerator__Vclpkg;
    Vtbench_top___024unit__03a__03adriver__Vclpkg* const __024unit__03a__03adriver__Vclpkg;
    Vtbench_top___024unit__03a__03aenvironment__Vclpkg* const __024unit__03a__03aenvironment__Vclpkg;
    Vtbench_top_test__03a__03amy_trans__Vclpkg* const test__03a__03amy_trans__Vclpkg;
    Vtbench_top_std__03a__03asemaphore__Vclpkg* const std__03a__03asemaphore__Vclpkg;
    Vtbench_top_std__03a__03aprocess__Vclpkg* const std__03a__03aprocess__Vclpkg;
    Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg* const std__03a__03amailbox__Tz1__Vclpkg;

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vtbench_top___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vtbench_top(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vtbench_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vtbench_top();
  private:
    VL_UNCOPYABLE(Vtbench_top);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); eval_end_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Trace signals in the model; called by application code
    void trace(VerilatedTraceBaseC* tfp, int levels, int options = 0) { contextp()->trace(tfp, levels, options); }
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    /// Prepare for cloning the model at the process level (e.g. fork in Linux)
    /// Release necessary resources. Called before cloning.
    void prepareClone() const;
    /// Re-init after cloning the model at the process level (e.g. fork in Linux)
    /// Re-allocate necessary resources. Called after cloning.
    void atClone() const;
    std::unique_ptr<VerilatedTraceConfig> traceConfig() const override final;
  private:
    // Internal functions - trace registration
    void traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options);
};

#endif  // guard
