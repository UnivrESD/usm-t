// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit__03a__03adriver__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03aenvironment__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03agenerator__Vclpkg.h"

VlCoroutine Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_post_test(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_post_test\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    if ((1U & (~ this->__PVT__gen_ended.isTriggered()))) {
        CData/*0:0*/ __VdynTrigger_haf48db4d__0;
        __VdynTrigger_haf48db4d__0 = 0;
        __VdynTrigger_haf48db4d__0 = 0U;
        while ((1U & (~ (IData)(__VdynTrigger_haf48db4d__0)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@([true] $unit::environment.gen_ended.isTriggered())", 
                                                         "tb/environment.sv", 
                                                         44);
            __VdynTrigger_haf48db4d__0 = this->__PVT__gen_ended.isTriggered();
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_haf48db4d__0);
            co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                         nullptr, 
                                                         "@([true] $unit::environment.gen_ended.isTriggered())", 
                                                         "tb/environment.sv", 
                                                         44);
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@([true] $unit::environment.gen_ended.isTriggered())", 
                                                     "tb/environment.sv", 
                                                     44);
    }
    if ((VL_NULL_CHECK(this->__PVT__gen, "tb/environment.sv", 45)
         ->__PVT__repeat_count != VL_NULL_CHECK(this->__PVT__driv, "tb/environment.sv", 45)
         ->__PVT__no_transactions)) {
        CData/*0:0*/ __VdynTrigger_hd4da1575__0;
        __VdynTrigger_hd4da1575__0 = 0;
        __VdynTrigger_hd4da1575__0 = 0U;
        CData/*0:0*/ __Vtrigcurrexpr_hae95f9cc__0;
        __Vtrigcurrexpr_hae95f9cc__0 = 0;
        while ((1U & (~ (IData)(__VdynTrigger_hd4da1575__0)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@([true] ($unit::environment.gen.repeat_count == $unit::environment.driv.no_transactions))", 
                                                         "tb/environment.sv", 
                                                         45);
            __Vtrigcurrexpr_hae95f9cc__0 = (VL_NULL_CHECK(this->__PVT__gen, "tb/environment.sv", 45)
                                            ->__PVT__repeat_count 
                                            == VL_NULL_CHECK(this->__PVT__driv, "tb/environment.sv", 45)
                                            ->__PVT__no_transactions);
            __VdynTrigger_hd4da1575__0 = __Vtrigcurrexpr_hae95f9cc__0;
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hd4da1575__0);
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@([true] ($unit::environment.gen.repeat_count == $unit::environment.driv.no_transactions))", 
                                                     "tb/environment.sv", 
                                                     45);
    }
}
