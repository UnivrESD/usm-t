// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP_TEST_H_
#define VERILATED_VTBENCH_TOP_TEST_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"
class Vtbench_top___024unit__03a__03aenvironment;
class Vtbench_top___024unit__03a__03agenerator;
class Vtbench_top___024unit__03a__03atransaction;
class Vtbench_top_test__03a__03amy_trans;


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top_test final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top_test(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top_test();
    VL_UNCOPYABLE(Vtbench_top_test);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
