// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top___024unit__03a__03aenvironment__Vclpkg.h"

void Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_pre_test(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_pre_test\n"); );
}

void Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_test(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_test\n"); );
    // Body
    this->__VnoInFunc_test____Vfork_1__0(vlSymsp);
    this->__VnoInFunc_test____Vfork_1__1(vlSymsp);
}

VlCoroutine Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_run(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::__VnoInFunc_run\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    this->__VnoInFunc_pre_test(vlSymsp);
    this->__VnoInFunc_test(vlSymsp);
    co_await this->__VnoInFunc_post_test(vlSymsp);
    VL_FINISH_MT("tb/environment.sv", 53, "");
}

Vtbench_top___024unit__03a__03aenvironment::~Vtbench_top___024unit__03a__03aenvironment() {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vtbench_top___024unit__03a__03aenvironment>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vtbench_top___024unit__03a__03aenvironment::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vtbench_top___024unit__03a__03aenvironment::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03aenvironment::to_string_middle\n"); );
    // Body
    std::string out;
    out += "gen:" + VL_TO_STRING(__PVT__gen);
    out += ", driv:" + VL_TO_STRING(__PVT__driv);
    out += ", gen2driv:" + VL_TO_STRING(__PVT__gen2driv);
    out += ", gen_ended:" + VL_TO_STRING(__PVT__gen_ended);
    out += ", controller_vif:" + VL_TO_STRING(__PVT__controller_vif);
    return out;
}
