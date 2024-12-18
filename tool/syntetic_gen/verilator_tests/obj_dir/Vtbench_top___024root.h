// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP___024ROOT_H_
#define VERILATED_VTBENCH_TOP___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"
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


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top___024root final : public VerilatedModule {
  public:
    // CELLS
    Vtbench_top___024unit* __PVT____024unit;
    Vtbench_top_std* __PVT__std;
    Vtbench_top_controller_intf* __PVT__tbench_top__DOT__intf;
    Vtbench_top_test* __PVT__tbench_top__DOT__t1;
    Vtbench_top___024unit__03a__03atransaction__Vclpkg* __024unit__03a__03atransaction__Vclpkg;
    Vtbench_top___024unit__03a__03agenerator__Vclpkg* __024unit__03a__03agenerator__Vclpkg;
    Vtbench_top___024unit__03a__03adriver__Vclpkg* __024unit__03a__03adriver__Vclpkg;
    Vtbench_top___024unit__03a__03aenvironment__Vclpkg* __024unit__03a__03aenvironment__Vclpkg;
    Vtbench_top_test__03a__03amy_trans__Vclpkg* test__03a__03amy_trans__Vclpkg;
    Vtbench_top_std__03a__03asemaphore__Vclpkg* std__03a__03asemaphore__Vclpkg;
    Vtbench_top_std__03a__03aprocess__Vclpkg* std__03a__03aprocess__Vclpkg;
    Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg* std__03a__03amailbox__Tz1__Vclpkg;

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tbench_top__DOT__DUT__DOT__clock;
    CData/*0:0*/ tbench_top__DOT__clk;
    CData/*0:0*/ tbench_top__DOT__rst;
    CData/*0:0*/ tbench_top__DOT__DUT__DOT___01_;
    CData/*0:0*/ tbench_top__DOT__DUT__DOT___18_;
    CData/*0:0*/ __VvifTrigger_h96fbb1c3__0;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tbench_top__DOT__DUT__DOT__clock__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlDelayScheduler __VdlySched;
    VlDynamicTriggerScheduler __VdynSched;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<2> __VicoTriggered;
    VlTriggerVec<4> __VactTriggered;
    VlTriggerVec<4> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top___024root(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top___024root();
    VL_UNCOPYABLE(Vtbench_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
