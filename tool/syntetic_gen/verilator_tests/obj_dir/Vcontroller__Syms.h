// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCONTROLLER__SYMS_H_
#define VERILATED_VCONTROLLER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vcontroller.h"

// INCLUDE MODULE CLASSES
#include "Vcontroller___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vcontroller__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vcontroller* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vcontroller___024root          TOP;

    // CONSTRUCTORS
    Vcontroller__Syms(VerilatedContext* contextp, const char* namep, Vcontroller* modelp);
    ~Vcontroller__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
