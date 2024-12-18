// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top_std__03a__03asemaphore__Vclpkg.h"

void Vtbench_top_std__03a__03asemaphore__Vclpkg___ctor_var_reset(Vtbench_top_std__03a__03asemaphore__Vclpkg* vlSelf);

Vtbench_top_std__03a__03asemaphore__Vclpkg::Vtbench_top_std__03a__03asemaphore__Vclpkg(Vtbench_top__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtbench_top_std__03a__03asemaphore__Vclpkg___ctor_var_reset(this);
}

void Vtbench_top_std__03a__03asemaphore__Vclpkg::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtbench_top_std__03a__03asemaphore__Vclpkg::~Vtbench_top_std__03a__03asemaphore__Vclpkg() {
}
