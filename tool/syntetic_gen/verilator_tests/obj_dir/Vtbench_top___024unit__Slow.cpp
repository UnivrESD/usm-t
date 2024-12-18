// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit.h"

void Vtbench_top___024unit___ctor_var_reset(Vtbench_top___024unit* vlSelf);

Vtbench_top___024unit::Vtbench_top___024unit(Vtbench_top__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtbench_top___024unit___ctor_var_reset(this);
}

void Vtbench_top___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtbench_top___024unit::~Vtbench_top___024unit() {
}
