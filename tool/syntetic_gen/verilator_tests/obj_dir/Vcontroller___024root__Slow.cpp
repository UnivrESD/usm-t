// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcontroller.h for the primary calling header

#include "Vcontroller__pch.h"
#include "Vcontroller__Syms.h"
#include "Vcontroller___024root.h"

void Vcontroller___024root___ctor_var_reset(Vcontroller___024root* vlSelf);

Vcontroller___024root::Vcontroller___024root(Vcontroller__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcontroller___024root___ctor_var_reset(this);
}

void Vcontroller___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vcontroller___024root::~Vcontroller___024root() {
}
