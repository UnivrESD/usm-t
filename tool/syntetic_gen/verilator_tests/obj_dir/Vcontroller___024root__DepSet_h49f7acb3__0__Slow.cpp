// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcontroller.h for the primary calling header

#include "Vcontroller__pch.h"
#include "Vcontroller__Syms.h"
#include "Vcontroller___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcontroller___024root___dump_triggers__stl(Vcontroller___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcontroller___024root___eval_triggers__stl(Vcontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontroller___024root___eval_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.set(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcontroller___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
