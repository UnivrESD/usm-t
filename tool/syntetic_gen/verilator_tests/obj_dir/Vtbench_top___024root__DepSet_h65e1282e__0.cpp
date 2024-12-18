// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024root.h"

VL_ATTR_COLD void Vtbench_top___024root___eval_initial__TOP(Vtbench_top___024root* vlSelf);
VlCoroutine Vtbench_top___024root___eval_initial__TOP__Vtiming__0(Vtbench_top___024root* vlSelf);
VlCoroutine Vtbench_top_test___eval_initial__TOP__tbench_top__DOT__t1__Vtiming__0(Vtbench_top_test* vlSelf);

void Vtbench_top___024root___eval_initial(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtbench_top___024root___eval_initial__TOP(vlSelf);
    Vtbench_top___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtbench_top_test___eval_initial__TOP__tbench_top__DOT__t1__Vtiming__0((&vlSymsp->TOP__tbench_top__DOT__t1));
    vlSelfRef.__Vtrigprevexpr___TOP__tbench_top__DOT__DUT__DOT__clock__0 
        = vlSelfRef.tbench_top__DOT__DUT__DOT__clock;
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtbench_top___024root___dump_triggers__ico(Vtbench_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtbench_top___024root___eval_triggers__ico(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_triggers__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.set(0U, (IData)(vlSelfRef.__VicoFirstIteration));
    vlSelfRef.__VicoTriggered.set(1U, (IData)(vlSelfRef.__VvifTrigger_h96fbb1c3__0));
    vlSelfRef.__VvifTrigger_h96fbb1c3__0 = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtbench_top___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vtbench_top___024root___ico_sequent__TOP__0(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___ico_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tbench_top__DOT__DUT__DOT___01_ = ((IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_1) 
                                                 & ((IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_2) 
                                                    & (IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_3)));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtbench_top___024root___dump_triggers__act(Vtbench_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtbench_top___024root___eval_triggers__act(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___eval_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.set(0U, (IData)(vlSelfRef.__VvifTrigger_h96fbb1c3__0));
    vlSelfRef.__VvifTrigger_h96fbb1c3__0 = 0U;
    vlSelfRef.__VactTriggered.set(1U, ((IData)(vlSelfRef.tbench_top__DOT__DUT__DOT__clock) 
                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tbench_top__DOT__DUT__DOT__clock__0))));
    vlSelfRef.__VactTriggered.set(2U, vlSelfRef.__VdlySched.awaitingCurrentTime());
    vlSelfRef.__VactTriggered.set(3U, vlSelfRef.__VdynSched.evaluate());
    vlSelfRef.__Vtrigprevexpr___TOP__tbench_top__DOT__DUT__DOT__clock__0 
        = vlSelfRef.tbench_top__DOT__DUT__DOT__clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtbench_top___024root___dump_triggers__act(vlSelf);
    }
#endif
    vlSelfRef.__VdynSched.doPostUpdates();
}

VL_INLINE_OPT void Vtbench_top___024root___act_sequent__TOP__0(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___act_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSymsp->TOP__tbench_top__DOT__intf.clk = vlSelfRef.tbench_top__DOT__clk;
    vlSelfRef.__VvifTrigger_h96fbb1c3__0 = 1U;
}

VL_INLINE_OPT void Vtbench_top___024root___nba_sequent__TOP__2(Vtbench_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root___nba_sequent__TOP__2\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tbench_top__DOT__DUT__DOT___18_ = vlSymsp->TOP__tbench_top__DOT__intf.a_0;
}
