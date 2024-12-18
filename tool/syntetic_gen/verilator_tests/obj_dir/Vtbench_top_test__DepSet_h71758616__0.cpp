// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit__03a__03aenvironment__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03agenerator__Vclpkg.h"
#include "Vtbench_top_test.h"
#include "Vtbench_top_test__03a__03amy_trans__Vclpkg.h"

VL_INLINE_OPT VlCoroutine Vtbench_top_test___eval_initial__TOP__tbench_top__DOT__t1__Vtiming__0(Vtbench_top_test* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtbench_top_test___eval_initial__TOP__tbench_top__DOT__t1__Vtiming__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlClassRef<Vtbench_top___024unit__03a__03aenvironment> __PVT__env;
    VlClassRef<Vtbench_top_test__03a__03amy_trans> __PVT__my_tr;
    // Body
    __PVT__env = VL_NEW(Vtbench_top___024unit__03a__03aenvironment, vlSymsp, vlSelf);
    __PVT__my_tr = VL_NEW(Vtbench_top_test__03a__03amy_trans, vlSymsp);
    VL_NULL_CHECK(VL_NULL_CHECK(__PVT__env, "tb/test.sv", 24)
                  ->__PVT__gen, "tb/test.sv", 24)->__PVT__repeat_count = 0x3e8U;
    VL_NULL_CHECK(VL_NULL_CHECK(__PVT__env, "tb/test.sv", 26)
                  ->__PVT__gen, "tb/test.sv", 26)->__PVT__trans 
        = __PVT__my_tr;
    co_await VL_NULL_CHECK(__PVT__env, "tb/test.sv", 29)->__VnoInFunc_run(vlSymsp);
}
