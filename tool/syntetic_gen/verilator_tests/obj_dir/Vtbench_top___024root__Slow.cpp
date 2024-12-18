// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024root.h"

void Vtbench_top___024root___ctor_var_reset(Vtbench_top___024root* vlSelf);

Vtbench_top___024root::Vtbench_top___024root(Vtbench_top__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __VdlySched{*symsp->_vm_contextp__}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtbench_top___024root___ctor_var_reset(this);
}

void Vtbench_top___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtbench_top___024root::~Vtbench_top___024root() {
}
