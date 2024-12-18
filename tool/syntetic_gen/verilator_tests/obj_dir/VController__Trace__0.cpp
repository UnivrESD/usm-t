// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VController__Syms.h"


void VController___024root__trace_chg_0_sub_0(VController___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void VController___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root__trace_chg_0\n"); );
    // Init
    VController___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VController___024root*>(voidSelf);
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    VController___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void VController___024root__trace_chg_0_sub_0(VController___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root__trace_chg_0_sub_0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgBit(oldp+0,(vlSelfRef.a_0));
    bufp->chgBit(oldp+1,(vlSelfRef.a_1));
    bufp->chgBit(oldp+2,(vlSelfRef.a_2));
    bufp->chgBit(oldp+3,(vlSelfRef.a_3));
    bufp->chgBit(oldp+4,(vlSelfRef.c_0));
    bufp->chgBit(oldp+5,(vlSelfRef.c_1));
    bufp->chgBit(oldp+6,(vlSelfRef.c_2));
    bufp->chgBit(oldp+7,(vlSelfRef.c_3));
    bufp->chgBit(oldp+8,(vlSelfRef.clock));
}

void VController___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VController___024root__trace_cleanup\n"); );
    // Init
    VController___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VController___024root*>(voidSelf);
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
