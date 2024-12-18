// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top___024unit__03a__03adriver__Vclpkg.h"

VlCoroutine Vtbench_top___024unit__03a__03adriver::__VnoInFunc_main(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top___024unit__03a__03adriver::__VnoInFunc_main\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    while (1U) {
        co_await this->__VnoInFunc_drive(vlSymsp);
    }
}

Vtbench_top___024unit__03a__03adriver::~Vtbench_top___024unit__03a__03adriver() {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top___024unit__03a__03adriver::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vtbench_top___024unit__03a__03adriver>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top___024unit__03a__03adriver::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vtbench_top___024unit__03a__03adriver::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top___024unit__03a__03adriver::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vtbench_top___024unit__03a__03adriver::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top___024unit__03a__03adriver::to_string_middle\n"); );
    // Body
    std::string out;
    out += "no_transactions:" + VL_TO_STRING(__PVT__no_transactions);
    out += ", controller_vif:" + VL_TO_STRING(__PVT__controller_vif);
    out += ", gen2driv:" + VL_TO_STRING(__PVT__gen2driv);
    return out;
}
