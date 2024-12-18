// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top___024unit__03a__03adriver__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03aenvironment__Vclpkg.h"

VL_INLINE_OPT VlCoroutine Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_test____Vfork_1__1(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_test____Vfork_1__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    co_await VL_NULL_CHECK(this->__PVT__driv, "tb/environment.sv", 39)->__VnoInFunc_main(vlSymsp);
}
