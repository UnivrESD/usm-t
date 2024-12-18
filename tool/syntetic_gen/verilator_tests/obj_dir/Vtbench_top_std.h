// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP_STD_H_
#define VERILATED_VTBENCH_TOP_STD_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top_std final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top_std(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top_std();
    VL_UNCOPYABLE(Vtbench_top_std);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
