// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit__03a__03adriver__Vclpkg.h"

Vtbench_top___024unit__03a__03adriver::Vtbench_top___024unit__03a__03adriver(Vtbench_top__Syms* __restrict vlSymsp, Vtbench_top_controller_intf* controller_vif, VlClassRef<Vtbench_top_std__03a__03amailbox__Tz1> gen2driv) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top___024unit__03a__03adriver::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    this->__PVT__controller_vif = controller_vif;
    this->__PVT__gen2driv = gen2driv;
}

void Vtbench_top___024unit__03a__03adriver::_ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top___024unit__03a__03adriver::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
    __PVT__no_transactions = 0;
    __PVT__controller_vif = nullptr;
    }
