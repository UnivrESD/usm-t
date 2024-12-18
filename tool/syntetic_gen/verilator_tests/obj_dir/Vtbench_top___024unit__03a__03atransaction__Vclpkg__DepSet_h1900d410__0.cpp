// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"

void Vtbench_top___024unit__03a__03atransaction::__VnoInFunc_do_copy(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> &do_copy__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::__VnoInFunc_do_copy\n"); );
    // Body
    VlClassRef<Vtbench_top___024unit__03a__03atransaction> trans;
    trans = VL_NEW(Vtbench_top___024unit__03a__03atransaction, vlSymsp);
    VL_NULL_CHECK(trans, "tb/transaction.sv", 20)->__PVT__a_0 
        = this->__PVT__a_0;
    VL_NULL_CHECK(trans, "tb/transaction.sv", 21)->__PVT__a_1 
        = this->__PVT__a_1;
    VL_NULL_CHECK(trans, "tb/transaction.sv", 22)->__PVT__a_2 
        = this->__PVT__a_2;
    VL_NULL_CHECK(trans, "tb/transaction.sv", 23)->__PVT__a_3 
        = this->__PVT__a_3;
    VL_NULL_CHECK(trans, "tb/transaction.sv", 24)->__PVT__a_4 
        = this->__PVT__a_4;
    do_copy__Vfuncrtn = trans;
}

Vtbench_top___024unit__03a__03atransaction::Vtbench_top___024unit__03a__03atransaction(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    IData/*31:0*/ unnamedblk2_1__DOT__i;
    unnamedblk2_1__DOT__i = 0;
    this->__Vrandmode.resize(5U);
    unnamedblk2_1__DOT__i = 0U;
    while ((unnamedblk2_1__DOT__i < this->__Vrandmode.size())) {
        this->__Vrandmode.atWrite(unnamedblk2_1__DOT__i) = 1U;
        unnamedblk2_1__DOT__i = ((IData)(1U) + unnamedblk2_1__DOT__i);
    }
}

void Vtbench_top___024unit__03a__03atransaction::_ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
    __PVT__a_0 = VL_RAND_RESET_I(1);
    __PVT__a_1 = VL_RAND_RESET_I(1);
    __PVT__a_2 = VL_RAND_RESET_I(1);
    __PVT__a_3 = VL_RAND_RESET_I(1);
    __PVT__a_4 = VL_RAND_RESET_I(1);
    __Vrandmode.atDefault() = VL_RAND_RESET_I(1);
}
