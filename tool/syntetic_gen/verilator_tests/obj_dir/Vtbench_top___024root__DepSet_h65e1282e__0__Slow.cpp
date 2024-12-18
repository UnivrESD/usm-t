// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024root.h"

VL_ATTR_COLD void Vtbench_top___024root___eval_initial__TOP(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_initial__TOP\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<4>/*127:0*/ __Vtemp_1;
    // Body
    vlSelfRef.tbench_top__DOT__clk = 0U;
    __Vtemp_1[0U] = 0x2e766364U;
    __Vtemp_1[1U] = 0x6c6c6572U;
    __Vtemp_1[2U] = 0x6e74726fU;
    __Vtemp_1[3U] = 0x636fU;
    vlSymsp->_vm_contextp__->dumpfile(VL_CVT_PACK_STR_NW(4, __Vtemp_1));
    vlSymsp->_traceDumpOpen();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtbench_top___024root___dump_triggers__stl(Vtbench_top___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtbench_top___024root___eval_triggers__stl(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.set(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtbench_top___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

VL_ATTR_COLD void Vtbench_top___024root___stl_sequent__TOP__0(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___stl_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSymsp->TOP__tbench_top__DOT__intf.clk = vlSelfRef.tbench_top__DOT__clk;
    vlSelfRef.__VvifTrigger_h96fbb1c3__0 = 1U;
    vlSelfRef.tbench_top__DOT__DUT__DOT___01_ = ((IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_1) 
                                                 & ((IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_2) 
                                                    & (IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_3)));
}
