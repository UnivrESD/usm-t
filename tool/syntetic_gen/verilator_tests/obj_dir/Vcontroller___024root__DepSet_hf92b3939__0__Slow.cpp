// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcontroller.h for the primary calling header

#include "Vcontroller__pch.h"
#include "Vcontroller___024root.h"

VL_ATTR_COLD void Vcontroller___024root___eval_static__TOP(Vcontroller___024root* vlSelf);

VL_ATTR_COLD void Vcontroller___024root___eval_static(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_static\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vcontroller___024root___eval_static__TOP(vlSelf);
}

VL_ATTR_COLD void Vcontroller___024root___eval_static__TOP(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_static__TOP\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.test__DOT___18_ = 0U;
}

VL_ATTR_COLD void Vcontroller___024root___eval_initial(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
}

VL_ATTR_COLD void Vcontroller___024root___eval_final(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_final\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontroller___024root___dump_triggers__stl(Vcontroller___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vcontroller___024root___eval_phase__stl(Vcontroller___024root* vlSelf);

VL_ATTR_COLD void Vcontroller___024root___eval_settle(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_settle\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vcontroller___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("controller.sv", 3, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vcontroller___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontroller___024root___dump_triggers__stl(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___dump_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

void Vcontroller___024root___ico_sequent__TOP__0(Vcontroller___024root* vlSelf);

VL_ATTR_COLD void Vcontroller___024root___eval_stl(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vcontroller___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vcontroller___024root___eval_triggers__stl(Vcontroller___024root* vlSelf);

VL_ATTR_COLD bool Vcontroller___024root___eval_phase__stl(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_phase__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vcontroller___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vcontroller___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontroller___024root___dump_triggers__ico(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___dump_triggers__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontroller___024root___dump_triggers__act(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___dump_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontroller___024root___dump_triggers__nba(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___dump_triggers__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcontroller___024root___ctor_var_reset(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->a_2 = VL_RAND_RESET_I(1);
    vlSelf->a_3 = VL_RAND_RESET_I(1);
    vlSelf->a_4 = VL_RAND_RESET_I(1);
    vlSelf->a_0 = VL_RAND_RESET_I(1);
    vlSelf->c_1 = VL_RAND_RESET_I(1);
    vlSelf->c_2 = VL_RAND_RESET_I(1);
    vlSelf->c_3 = VL_RAND_RESET_I(1);
    vlSelf->c_4 = VL_RAND_RESET_I(1);
    vlSelf->c_0 = VL_RAND_RESET_I(1);
    vlSelf->a_1 = VL_RAND_RESET_I(1);
    vlSelf->test__DOT___18_ = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_RAND_RESET_I(1);
}
