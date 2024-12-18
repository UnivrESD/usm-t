// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VController.h for the primary calling header

#include "VController__pch.h"
#include "VController___024root.h"

void VController___024root___ico_sequent__TOP__0(VController___024root* vlSelf);

void VController___024root___eval_ico(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___eval_ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VController___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void VController___024root___ico_sequent__TOP__0(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___ico_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.c_0 = vlSelfRef.a_0;
    vlSelfRef.Controller__DOT___01_ = ((IData)(vlSelfRef.a_1) 
                                       & (IData)(vlSelfRef.a_2));
    vlSelfRef.c_1 = (1U & (~ ((~ ((IData)(vlSelfRef.Controller__DOT___01_) 
                                  & ((IData)(vlSelfRef.a_3) 
                                     & ((IData)(vlSelfRef.Controller__DOT___11_) 
                                        & (IData)(vlSelfRef.a_0))))) 
                              & (~ ((IData)(vlSelfRef.Controller__DOT___01_) 
                                    & ((IData)(vlSelfRef.a_3) 
                                       & ((~ (IData)(vlSelfRef.a_0)) 
                                          & (IData)(vlSelfRef.Controller__DOT___11_))))))));
    vlSelfRef.c_2 = vlSelfRef.c_1;
    vlSelfRef.c_3 = vlSelfRef.c_1;
}

void VController___024root___eval_triggers__ico(VController___024root* vlSelf);

bool VController___024root___eval_phase__ico(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___eval_phase__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    VController___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        VController___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void VController___024root___eval_act(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void VController___024root___nba_sequent__TOP__0(VController___024root* vlSelf);

void VController___024root___eval_nba(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VController___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void VController___024root___nba_sequent__TOP__0(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.Controller__DOT___11_ = vlSelfRef.a_0;
    vlSelfRef.c_1 = (1U & (~ ((~ ((IData)(vlSelfRef.Controller__DOT___01_) 
                                  & ((IData)(vlSelfRef.a_3) 
                                     & ((IData)(vlSelfRef.Controller__DOT___11_) 
                                        & (IData)(vlSelfRef.a_0))))) 
                              & (~ ((IData)(vlSelfRef.Controller__DOT___01_) 
                                    & ((IData)(vlSelfRef.a_3) 
                                       & ((~ (IData)(vlSelfRef.a_0)) 
                                          & (IData)(vlSelfRef.Controller__DOT___11_))))))));
    vlSelfRef.c_2 = vlSelfRef.c_1;
    vlSelfRef.c_3 = vlSelfRef.c_1;
}

void VController___024root___eval_triggers__act(VController___024root* vlSelf);

bool VController___024root___eval_phase__act(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    VController___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        VController___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool VController___024root___eval_phase__nba(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        VController___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VController___024root___dump_triggers__ico(VController___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VController___024root___dump_triggers__nba(VController___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VController___024root___dump_triggers__act(VController___024root* vlSelf);
#endif  // VL_DEBUG

void VController___024root___eval(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___eval\n"); );
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
            VController___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("Controller.sv", 3, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (VController___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            VController___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("Controller.sv", 3, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                VController___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("Controller.sv", 3, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (VController___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (VController___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void VController___024root___eval_debug_assertions(VController___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelfRef.a_1 & 0xfeU))) {
        Verilated::overWidthError("a_1");}
    if (VL_UNLIKELY((vlSelfRef.a_2 & 0xfeU))) {
        Verilated::overWidthError("a_2");}
    if (VL_UNLIKELY((vlSelfRef.a_3 & 0xfeU))) {
        Verilated::overWidthError("a_3");}
    if (VL_UNLIKELY((vlSelfRef.a_0 & 0xfeU))) {
        Verilated::overWidthError("a_0");}
}
#endif  // VL_DEBUG
