// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top_std.h"

void Vtbench_top_std___ctor_var_reset(Vtbench_top_std* vlSelf);

Vtbench_top_std::Vtbench_top_std(Vtbench_top__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtbench_top_std___ctor_var_reset(this);
}

void Vtbench_top_std::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtbench_top_std::~Vtbench_top_std() {
}
