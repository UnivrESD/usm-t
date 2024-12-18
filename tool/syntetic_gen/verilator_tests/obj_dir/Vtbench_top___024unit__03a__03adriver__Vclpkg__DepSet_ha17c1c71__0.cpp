// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit__03a__03adriver__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"
#include "Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg.h"

VlCoroutine Vtbench_top___024unit__03a__03adriver::__VnoInFunc_drive(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top___024unit__03a__03adriver::__VnoInFunc_drive\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    VlClassRef<Vtbench_top___024unit__03a__03atransaction> trans;
    co_await VL_NULL_CHECK(this->__PVT__gen2driv, "tb/driver.sv", 25)->__VnoInFunc_get(vlSymsp, trans);
    CData/*0:0*/ __VdynTrigger_hd14ec536__0;
    __VdynTrigger_hd14ec536__0 = 0;
    __VdynTrigger_hd14ec536__0 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_hb321aa89__0;
    __Vtrigprevexpr_hb321aa89__0 = 0;
    __Vtrigprevexpr_hb321aa89__0 = VL_NULL_CHECK(this->__PVT__controller_vif, "tb/driver.sv", 27)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_hd14ec536__0)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(negedge $unit::driver.controller_vif.clk)", 
                                                     "tb/driver.sv", 
                                                     27);
        __VdynTrigger_hd14ec536__0 = ((~ (IData)(VL_NULL_CHECK(this->__PVT__controller_vif, "tb/driver.sv", 27)
                                                 ->clk)) 
                                      & (IData)(__Vtrigprevexpr_hb321aa89__0));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hd14ec536__0);
        __Vtrigprevexpr_hb321aa89__0 = VL_NULL_CHECK(this->__PVT__controller_vif, "tb/driver.sv", 27)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(negedge $unit::driver.controller_vif.clk)", 
                                                 "tb/driver.sv", 
                                                 27);
    VL_NULL_CHECK(this->__PVT__controller_vif, "tb/driver.sv", 30)->a_0 
        = VL_NULL_CHECK(trans, "tb/driver.sv", 30)->__PVT__a_0;
    vlSymsp->TOP.__VvifTrigger_h96fbb1c3__0 = 1U;
    VL_NULL_CHECK(this->__PVT__controller_vif, "tb/driver.sv", 31)->a_1 
        = VL_NULL_CHECK(trans, "tb/driver.sv", 31)->__PVT__a_1;
    VL_NULL_CHECK(this->__PVT__controller_vif, "tb/driver.sv", 32)->a_2 
        = VL_NULL_CHECK(trans, "tb/driver.sv", 32)->__PVT__a_2;
    VL_NULL_CHECK(this->__PVT__controller_vif, "tb/driver.sv", 33)->a_3 
        = VL_NULL_CHECK(trans, "tb/driver.sv", 33)->__PVT__a_3;
    VL_NULL_CHECK(this->__PVT__controller_vif, "tb/driver.sv", 34)->a_4 
        = VL_NULL_CHECK(trans, "tb/driver.sv", 34)->__PVT__a_4;
    this->__PVT__no_transactions = ((IData)(1U) + this->__PVT__no_transactions);
}
