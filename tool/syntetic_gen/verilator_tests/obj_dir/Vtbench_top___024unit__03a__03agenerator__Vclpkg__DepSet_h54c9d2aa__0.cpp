// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top___024unit__03a__03agenerator__Vclpkg.h"

Vtbench_top___024unit__03a__03agenerator::~Vtbench_top___024unit__03a__03agenerator() {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03agenerator::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vtbench_top___024unit__03a__03agenerator>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03agenerator::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vtbench_top___024unit__03a__03agenerator::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03agenerator::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vtbench_top___024unit__03a__03agenerator::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03agenerator::to_string_middle\n"); );
    // Body
    std::string out;
    out += "trans:" + VL_TO_STRING(__PVT__trans);
    out += ", tr:" + VL_TO_STRING(__PVT__tr);
    out += ", repeat_count:" + VL_TO_STRING(__PVT__repeat_count);
    out += ", gen2driv:" + VL_TO_STRING(__PVT__gen2driv);
    out += ", ended:" + VL_TO_STRING(__PVT__ended);
    return out;
}
