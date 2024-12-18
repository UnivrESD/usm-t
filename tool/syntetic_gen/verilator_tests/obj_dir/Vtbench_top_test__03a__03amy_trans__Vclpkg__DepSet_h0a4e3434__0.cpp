// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"
#include "Vtbench_top_test__03a__03amy_trans__Vclpkg.h"

void Vtbench_top_test__03a__03amy_trans::__VnoInFunc_pre_randomize(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top_test__03a__03amy_trans::__VnoInFunc_pre_randomize\n"); );
    // Body
    Vtbench_top___024unit__03a__03atransaction::__Vrandmode.atWrite(0U) = 1U;
    Vtbench_top___024unit__03a__03atransaction::__Vrandmode.atWrite(1U) = 1U;
    Vtbench_top___024unit__03a__03atransaction::__Vrandmode.atWrite(2U) = 1U;
    Vtbench_top___024unit__03a__03atransaction::__Vrandmode.atWrite(3U) = 1U;
    Vtbench_top___024unit__03a__03atransaction::__Vrandmode.atWrite(4U) = 1U;
}

void Vtbench_top_test__03a__03amy_trans::__VnoInFunc___Vbasic_randomize(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &__Vbasic_randomize__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top_test__03a__03amy_trans::__VnoInFunc___Vbasic_randomize\n"); );
    // Body
    __Vbasic_randomize__Vfuncrtn = 1U;
    if (Vtbench_top___024unit__03a__03atransaction::__Vrandmode.at(0U)) {
        Vtbench_top___024unit__03a__03atransaction::__PVT__a_0 
            = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
    if (Vtbench_top___024unit__03a__03atransaction::__Vrandmode.at(1U)) {
        Vtbench_top___024unit__03a__03atransaction::__PVT__a_1 
            = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
    if (Vtbench_top___024unit__03a__03atransaction::__Vrandmode.at(2U)) {
        Vtbench_top___024unit__03a__03atransaction::__PVT__a_2 
            = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
    if (Vtbench_top___024unit__03a__03atransaction::__Vrandmode.at(3U)) {
        Vtbench_top___024unit__03a__03atransaction::__PVT__a_3 
            = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
    if (Vtbench_top___024unit__03a__03atransaction::__Vrandmode.at(4U)) {
        Vtbench_top___024unit__03a__03atransaction::__PVT__a_4 
            = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
}
