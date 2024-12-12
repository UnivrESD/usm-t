// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtest.h for the primary calling header

#ifndef VERILATED_VTEST___024ROOT_H_
#define VERILATED_VTEST___024ROOT_H_  // guard

#include "verilated.h"


class Vtest__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtest___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(a_2,0,0);
    VL_IN8(a_3,0,0);
    VL_IN8(a_4,0,0);
    VL_IN8(a_0,0,0);
    VL_OUT8(c_1,0,0);
    VL_OUT8(c_2,0,0);
    VL_OUT8(c_3,0,0);
    VL_OUT8(c_4,0,0);
    VL_OUT8(c_0,0,0);
    VL_IN8(a_1,0,0);
    CData/*0:0*/ test__DOT___18_;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtest__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtest___024root(Vtest__Syms* symsp, const char* v__name);
    ~Vtest___024root();
    VL_UNCOPYABLE(Vtest___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
