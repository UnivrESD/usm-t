// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"
#include "Vtbench_top_test__03a__03amy_trans__Vclpkg.h"

Vtbench_top_test__03a__03amy_trans::Vtbench_top_test__03a__03amy_trans(Vtbench_top__Syms* __restrict vlSymsp)
    : Vtbench_top___024unit__03a__03atransaction(vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top_test__03a__03amy_trans::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    IData/*31:0*/ unnamedblk2_1__DOT__i;
    unnamedblk2_1__DOT__i = 0;
    ;
    Vtbench_top___024unit__03a__03atransaction::__Vrandmode.resize(5U);
    unnamedblk2_1__DOT__i = 0U;
    while ((unnamedblk2_1__DOT__i < Vtbench_top___024unit__03a__03atransaction::__Vrandmode.size())) {
        Vtbench_top___024unit__03a__03atransaction::__Vrandmode.atWrite(unnamedblk2_1__DOT__i) = 1U;
        unnamedblk2_1__DOT__i = ((IData)(1U) + unnamedblk2_1__DOT__i);
    }
}
