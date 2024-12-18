// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top_std.h"

VL_ATTR_COLD void Vtbench_top_std___ctor_var_reset(Vtbench_top_std* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top_std___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
