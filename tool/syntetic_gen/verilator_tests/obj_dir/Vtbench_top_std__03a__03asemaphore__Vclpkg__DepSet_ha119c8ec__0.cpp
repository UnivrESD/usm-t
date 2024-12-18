// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top_std__03a__03asemaphore__Vclpkg.h"

Vtbench_top_std__03a__03asemaphore::Vtbench_top_std__03a__03asemaphore(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03asemaphore::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    this->__PVT__m_keyCount = keyCount;
}

VlCoroutine Vtbench_top_std__03a__03asemaphore::__VnoInFunc_get(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03asemaphore::__VnoInFunc_get\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    while (VL_LTS_III(32, this->__PVT__m_keyCount, keyCount)) {
        if (VL_LTS_III(32, this->__PVT__m_keyCount, keyCount)) {
            CData/*0:0*/ __VdynTrigger_h41d77514__0;
            __VdynTrigger_h41d77514__0 = 0;
            __VdynTrigger_h41d77514__0 = 0U;
            CData/*0:0*/ __Vtrigcurrexpr_h43985a3d__0;
            __Vtrigcurrexpr_h43985a3d__0 = 0;
            while ((1U & (~ (IData)(__VdynTrigger_h41d77514__0)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@([true] (std::semaphore.m_keyCount >= std::semaphore.keyCount))", 
                                                             "/usr/local/share/verilator/include/verilated_std.sv", 
                                                             109);
                __Vtrigcurrexpr_h43985a3d__0 = VL_GTES_III(32, this->__PVT__m_keyCount, keyCount);
                __VdynTrigger_h41d77514__0 = __Vtrigcurrexpr_h43985a3d__0;
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h41d77514__0);
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@([true] (std::semaphore.m_keyCount >= std::semaphore.keyCount))", 
                                                         "/usr/local/share/verilator/include/verilated_std.sv", 
                                                         109);
        }
    }
    this->__PVT__m_keyCount = (this->__PVT__m_keyCount 
                               - keyCount);
}

void Vtbench_top_std__03a__03asemaphore::_ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03asemaphore::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
    __PVT__m_keyCount = 0;
}
