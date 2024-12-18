// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit__03a__03agenerator__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"

Vtbench_top___024unit__03a__03agenerator::Vtbench_top___024unit__03a__03agenerator(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top_std__03a__03amailbox__Tz1> gen2driv, VlAssignableEvent ended) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03agenerator::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    this->__PVT__gen2driv = gen2driv;
    this->__PVT__ended = ended;
    this->__PVT__trans = VL_NEW(Vtbench_top___024unit__03a__03atransaction, vlSymsp);
}
