// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP___024UNIT_H_
#define VERILATED_VTBENCH_TOP___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top___024unit(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top___024unit();
    VL_UNCOPYABLE(Vtbench_top___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
