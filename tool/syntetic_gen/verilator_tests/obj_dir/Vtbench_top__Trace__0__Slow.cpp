// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtbench_top__Syms.h"


VL_ATTR_COLD void Vtbench_top___024root__trace_init_sub__TOP__tbench_top__DOT__intf__0(Vtbench_top___024root* vlSelf, VerilatedVcd* tracep);
VL_ATTR_COLD void Vtbench_top___024root__trace_init_sub__TOP__tbench_top__DOT__t1__0(Vtbench_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vtbench_top___024root__trace_init_sub__TOP__0(Vtbench_top___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root__trace_init_sub__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushPrefix("tbench_top", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+1,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+4,0,"rst",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("intf", VerilatedTracePrefixType::SCOPE_INTERFACE);
    Vtbench_top___024root__trace_init_sub__TOP__tbench_top__DOT__intf__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->pushPrefix("t1", VerilatedTracePrefixType::SCOPE_MODULE);
    Vtbench_top___024root__trace_init_sub__TOP__tbench_top__DOT__t1__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->pushPrefix("DUT", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("intf", VerilatedTracePrefixType::SCOPE_INTERFACE);
    Vtbench_top___024root__trace_init_sub__TOP__tbench_top__DOT__intf__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->declBit(c+5,0,"clock",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtbench_top___024root__trace_init_sub__TOP__tbench_top__DOT__t1__0(Vtbench_top___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root__trace_init_sub__TOP__tbench_top__DOT__t1__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
}

VL_ATTR_COLD void Vtbench_top___024root__trace_init_sub__TOP__tbench_top__DOT__intf__0(Vtbench_top___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root__trace_init_sub__TOP__tbench_top__DOT__intf__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+2,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"a_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+7,0,"a_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"a_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"a_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"a_4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"c_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"c_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"c_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"c_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"c_4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
}

VL_ATTR_COLD void Vtbench_top___024root__trace_init_top(Vtbench_top___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root__trace_init_top\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtbench_top___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtbench_top___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vtbench_top___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtbench_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtbench_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtbench_top___024root__trace_register(Vtbench_top___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root__trace_register\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtbench_top___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vtbench_top___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vtbench_top___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vtbench_top___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtbench_top___024root__trace_const_0_sub_0(Vtbench_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtbench_top___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root__trace_const_0\n"); );
    // Init
    Vtbench_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtbench_top___024root*>(voidSelf);
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtbench_top___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtbench_top___024root__trace_const_0_sub_0(Vtbench_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root__trace_const_0_sub_0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+4,(vlSelfRef.tbench_top__DOT__rst));
    bufp->fullBit(oldp+5,(vlSelfRef.tbench_top__DOT__DUT__DOT__clock));
    bufp->fullBit(oldp+6,(vlSymsp->TOP__tbench_top__DOT__intf.a_0));
    bufp->fullBit(oldp+7,(vlSymsp->TOP__tbench_top__DOT__intf.a_1));
    bufp->fullBit(oldp+8,(vlSymsp->TOP__tbench_top__DOT__intf.a_2));
    bufp->fullBit(oldp+9,(vlSymsp->TOP__tbench_top__DOT__intf.a_3));
    bufp->fullBit(oldp+10,(vlSymsp->TOP__tbench_top__DOT__intf.a_4));
}

VL_ATTR_COLD void Vtbench_top___024root__trace_full_0_sub_0(Vtbench_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtbench_top___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root__trace_full_0\n"); );
    // Init
    Vtbench_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtbench_top___024root*>(voidSelf);
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtbench_top___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtbench_top___024root__trace_full_0_sub_0(Vtbench_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtbench_top___024root__trace_full_0_sub_0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelfRef.tbench_top__DOT__clk));
    bufp->fullBit(oldp+2,(vlSymsp->TOP__tbench_top__DOT__intf.clk));
    bufp->fullBit(oldp+3,((1U & (~ ((~ ((IData)(vlSelfRef.tbench_top__DOT__DUT__DOT___01_) 
                                        & ((IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_4) 
                                           & ((IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_0) 
                                              & (~ (IData)(vlSelfRef.tbench_top__DOT__DUT__DOT___18_)))))) 
                                    & ((~ ((IData)(vlSelfRef.tbench_top__DOT__DUT__DOT___01_) 
                                           & ((IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_4) 
                                              & ((IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_0) 
                                                 & (IData)(vlSelfRef.tbench_top__DOT__DUT__DOT___18_))))) 
                                       & (~ ((IData)(vlSelfRef.tbench_top__DOT__DUT__DOT___01_) 
                                             & ((IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_4) 
                                                & ((~ (IData)(vlSymsp->TOP__tbench_top__DOT__intf.a_0)) 
                                                   & (IData)(vlSelfRef.tbench_top__DOT__DUT__DOT___18_)))))))))));
}
