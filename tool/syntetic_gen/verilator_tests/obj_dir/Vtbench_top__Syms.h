// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTBENCH_TOP__SYMS_H_
#define VERILATED_VTBENCH_TOP__SYMS_H_  // guard

#include "verilated.h"
#include "verilated_vcd_c.h"

// INCLUDE MODEL CLASS

#include "Vtbench_top.h"

// INCLUDE MODULE CLASSES
#include "Vtbench_top___024root.h"
#include "Vtbench_top___024unit.h"
#include "Vtbench_top_test.h"
#include "Vtbench_top_std.h"
#include "Vtbench_top_controller_intf.h"
#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03agenerator__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03adriver__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03aenvironment__Vclpkg.h"
#include "Vtbench_top_test__03a__03amy_trans__Vclpkg.h"
#include "Vtbench_top_std__03a__03asemaphore__Vclpkg.h"
#include "Vtbench_top_std__03a__03aprocess__Vclpkg.h"
#include "Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vtbench_top__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtbench_top* const __Vm_modelp;
    bool __Vm_dumping = false;  // Dumping is active
    VerilatedMutex __Vm_dumperMutex;  // Protect __Vm_dumperp
    VerilatedVcdC* __Vm_dumperp VL_GUARDED_BY(__Vm_dumperMutex) = nullptr;  /// Trace class for $dump*
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    std::vector<VlAssignableEvent> __Vm_triggeredEvents;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtbench_top___024root          TOP;
    Vtbench_top___024unit__03a__03adriver__Vclpkg TOP____024unit__03a__03adriver__Vclpkg;
    Vtbench_top___024unit__03a__03aenvironment__Vclpkg TOP____024unit__03a__03aenvironment__Vclpkg;
    Vtbench_top___024unit__03a__03agenerator__Vclpkg TOP____024unit__03a__03agenerator__Vclpkg;
    Vtbench_top___024unit__03a__03atransaction__Vclpkg TOP____024unit__03a__03atransaction__Vclpkg;
    Vtbench_top___024unit          TOP____024unit;
    Vtbench_top_std                TOP__std;
    Vtbench_top_controller_intf    TOP__tbench_top__DOT__intf;
    Vtbench_top_test               TOP__tbench_top__DOT__t1;
    Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg TOP__std__03a__03amailbox__Tz1__Vclpkg;
    Vtbench_top_std__03a__03aprocess__Vclpkg TOP__std__03a__03aprocess__Vclpkg;
    Vtbench_top_std__03a__03asemaphore__Vclpkg TOP__std__03a__03asemaphore__Vclpkg;
    Vtbench_top_test__03a__03amy_trans__Vclpkg TOP__test__03a__03amy_trans__Vclpkg;

    // SCOPE NAMES
    VerilatedScope __Vscope___024unit__generator;
    VerilatedScope __Vscope___024unit__generator__main__unnamedblk1_1;
    VerilatedScope __Vscope_std__process;
    VerilatedScope __Vscope_std__process__suspend;

    // CONSTRUCTORS
    Vtbench_top__Syms(VerilatedContext* contextp, const char* namep, Vtbench_top* modelp);
    ~Vtbench_top__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
    void fireEvent(VlAssignableEvent& event) {
        if (VL_LIKELY(!event.isTriggered())) {
            __Vm_triggeredEvents.push_back(event);
        }
        event.fire();
    }
    void clearTriggeredEvents() {
        for (auto& event : __Vm_triggeredEvents) event.clearTriggered();
        __Vm_triggeredEvents.clear();
    }
    void _traceDump();
    void _traceDumpOpen();
    void _traceDumpClose();
};

#endif  // guard
