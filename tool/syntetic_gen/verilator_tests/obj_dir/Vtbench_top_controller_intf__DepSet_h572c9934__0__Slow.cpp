// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top_controller_intf.h"

VL_ATTR_COLD void Vtbench_top_controller_intf___ctor_var_reset(Vtbench_top_controller_intf* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtbench_top_controller_intf___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->a_0 = VL_RAND_RESET_I(1);
    vlSelf->a_1 = VL_RAND_RESET_I(1);
    vlSelf->a_2 = VL_RAND_RESET_I(1);
    vlSelf->a_3 = VL_RAND_RESET_I(1);
    vlSelf->a_4 = VL_RAND_RESET_I(1);
}
