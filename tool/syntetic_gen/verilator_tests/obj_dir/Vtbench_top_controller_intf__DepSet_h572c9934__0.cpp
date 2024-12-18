// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top_controller_intf.h"

std::string VL_TO_STRING(const Vtbench_top_controller_intf* obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtbench_top_controller_intf::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->name() : "null");
}
