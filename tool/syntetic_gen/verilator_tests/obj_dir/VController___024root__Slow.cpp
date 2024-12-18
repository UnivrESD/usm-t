// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VController.h for the primary calling header

#include "VController__pch.h"
#include "VController__Syms.h"
#include "VController___024root.h"

void VController___024root___ctor_var_reset(VController___024root* vlSelf);

VController___024root::VController___024root(VController__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    VController___024root___ctor_var_reset(this);
}

void VController___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VController___024root::~VController___024root() {
}
