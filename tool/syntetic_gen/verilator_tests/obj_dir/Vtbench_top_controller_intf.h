// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP_CONTROLLER_INTF_H_
#define VERILATED_VTBENCH_TOP_CONTROLLER_INTF_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top_controller_intf final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    CData/*0:0*/ a_0;
    CData/*0:0*/ a_1;
    CData/*0:0*/ a_2;
    CData/*0:0*/ a_3;
    CData/*0:0*/ a_4;

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top_controller_intf(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top_controller_intf();
    VL_UNCOPYABLE(Vtbench_top_controller_intf);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

std::string VL_TO_STRING(const Vtbench_top_controller_intf* obj);

#endif  // guard
