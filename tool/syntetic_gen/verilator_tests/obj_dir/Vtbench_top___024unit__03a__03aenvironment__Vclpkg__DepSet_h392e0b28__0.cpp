// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit__03a__03adriver__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03aenvironment__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03agenerator__Vclpkg.h"
#include "Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg.h"

Vtbench_top___024unit__03a__03aenvironment::Vtbench_top___024unit__03a__03aenvironment(Vtbench_top__Syms* __restrict vlSymsp, Vtbench_top_controller_intf* controller_vif) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    this->__PVT__controller_vif = controller_vif;
    this->__PVT__gen2driv = VL_NEW(Vtbench_top_std__03a__03amailbox__Tz1, vlSymsp, 0U);
    this->__PVT__gen = VL_NEW(Vtbench_top___024unit__03a__03agenerator, vlSymsp, this->__PVT__gen2driv, this->__PVT__gen_ended);
    this->__PVT__driv = VL_NEW(Vtbench_top___024unit__03a__03adriver, vlSymsp, controller_vif, this->__PVT__gen2driv);
}
