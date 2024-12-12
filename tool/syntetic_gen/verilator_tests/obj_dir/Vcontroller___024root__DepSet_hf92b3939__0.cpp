// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcontroller.h for the primary calling header

#include "Vcontroller__pch.h"
#include "Vcontroller___024root.h"

void Vcontroller___024root___ico_sequent__TOP__0(Vcontroller___024root* vlSelf);

void Vcontroller___024root___eval_ico(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vcontroller___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vcontroller___024root___ico_sequent__TOP__0(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___ico_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.c_0 = vlSelfRef.a_0;
    vlSelfRef.c_1 = (((IData)(vlSelfRef.a_1) & ((IData)(vlSelfRef.a_2) 
                                                & (IData)(vlSelfRef.a_3))) 
                     & ((IData)(vlSelfRef.a_4) & ((
                                                   (~ (IData)(vlSelfRef.test__DOT___18_)) 
                                                   & (IData)(vlSelfRef.a_0)) 
                                                  | (1U 
                                                     & (IData)(vlSelfRef.test__DOT___18_)))));
    vlSelfRef.c_2 = vlSelfRef.c_1;
    vlSelfRef.c_3 = vlSelfRef.c_1;
    vlSelfRef.c_4 = vlSelfRef.c_1;
}

void Vcontroller___024root___eval_triggers__ico(Vcontroller___024root* vlSelf);

bool Vcontroller___024root___eval_phase__ico(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_phase__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vcontroller___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vcontroller___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vcontroller___024root___eval_act(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vcontroller___024root___nba_sequent__TOP__0(Vcontroller___024root* vlSelf);

void Vcontroller___024root___eval_nba(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vcontroller___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vcontroller___024root___nba_sequent__TOP__0(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.test__DOT___18_ = vlSelfRef.a_0;
    vlSelfRef.c_1 = (((IData)(vlSelfRef.a_1) & ((IData)(vlSelfRef.a_2) 
                                                & (IData)(vlSelfRef.a_3))) 
                     & ((IData)(vlSelfRef.a_4) & ((
                                                   (~ (IData)(vlSelfRef.test__DOT___18_)) 
                                                   & (IData)(vlSelfRef.a_0)) 
                                                  | (1U 
                                                     & (IData)(vlSelfRef.test__DOT___18_)))));
    vlSelfRef.c_2 = vlSelfRef.c_1;
    vlSelfRef.c_3 = vlSelfRef.c_1;
    vlSelfRef.c_4 = vlSelfRef.c_1;
}

void Vcontroller___024root___eval_triggers__act(Vcontroller___024root* vlSelf);

bool Vcontroller___024root___eval_phase__act(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vcontroller___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vcontroller___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vcontroller___024root___eval_phase__nba(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vcontroller___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontroller___024root___dump_triggers__ico(Vcontroller___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontroller___024root___dump_triggers__nba(Vcontroller___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontroller___024root___dump_triggers__act(Vcontroller___024root* vlSelf);
#endif  // VL_DEBUG

void Vcontroller___024root___eval(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vcontroller___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("controller.sv", 3, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vcontroller___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vcontroller___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("controller.sv", 3, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vcontroller___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("controller.sv", 3, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vcontroller___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vcontroller___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vcontroller___024root___eval_debug_assertions(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelfRef.a_2 & 0xfeU))) {
        Verilated::overWidthError("a_2");}
    if (VL_UNLIKELY((vlSelfRef.a_3 & 0xfeU))) {
        Verilated::overWidthError("a_3");}
    if (VL_UNLIKELY((vlSelfRef.a_4 & 0xfeU))) {
        Verilated::overWidthError("a_4");}
    if (VL_UNLIKELY((vlSelfRef.a_0 & 0xfeU))) {
        Verilated::overWidthError("a_0");}
    if (VL_UNLIKELY((vlSelfRef.a_1 & 0xfeU))) {
        Verilated::overWidthError("a_1");}
}
#endif  // VL_DEBUG
