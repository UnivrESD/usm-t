// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg.h"

Vtbench_top_std__03a__03amailbox__Tz1::Vtbench_top_std__03a__03amailbox__Tz1(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ bound) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03amailbox__Tz1::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    this->__PVT__m_bound = bound;
}

VlCoroutine Vtbench_top_std__03a__03amailbox__Tz1::__VnoInFunc_put(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> message) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03amailbox__Tz1::__VnoInFunc_put\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    while (((0U != this->__PVT__m_bound) & VL_GTES_III(32, this->__PVT__m_queue.size(), this->__PVT__m_bound))) {
        if (VL_GTES_III(32, this->__PVT__m_queue.size(), this->__PVT__m_bound)) {
            CData/*0:0*/ __VdynTrigger_h89eb947c__0;
            __VdynTrigger_h89eb947c__0 = 0;
            __VdynTrigger_h89eb947c__0 = 0U;
            CData/*0:0*/ __Vtrigcurrexpr_h7c0478a5__0;
            __Vtrigcurrexpr_h7c0478a5__0 = 0;
            while ((1U & (~ (IData)(__VdynTrigger_h89eb947c__0)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@([true] (std::mailbox__Tz1.m_queue.size() < std::mailbox__Tz1.m_bound))", 
                                                             "/usr/local/share/verilator/include/verilated_std.sv", 
                                                             47);
                __Vtrigcurrexpr_h7c0478a5__0 = VL_LTS_III(32, this->__PVT__m_queue.size(), this->__PVT__m_bound);
                __VdynTrigger_h89eb947c__0 = __Vtrigcurrexpr_h7c0478a5__0;
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h89eb947c__0);
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@([true] (std::mailbox__Tz1.m_queue.size() < std::mailbox__Tz1.m_bound))", 
                                                         "/usr/local/share/verilator/include/verilated_std.sv", 
                                                         47);
        }
    }
    this->__PVT__m_queue.push_back(message);
}

VlCoroutine Vtbench_top_std__03a__03amailbox__Tz1::__VnoInFunc_get(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> &message) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03amailbox__Tz1::__VnoInFunc_get\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    while ((0U == this->__PVT__m_queue.size())) {
        if (VL_GTES_III(32, 0U, this->__PVT__m_queue.size())) {
            CData/*0:0*/ __VdynTrigger_h621ad74f__0;
            __VdynTrigger_h621ad74f__0 = 0;
            __VdynTrigger_h621ad74f__0 = 0U;
            CData/*0:0*/ __Vtrigcurrexpr_h63d4b802__0;
            __Vtrigcurrexpr_h63d4b802__0 = 0;
            while ((1U & (~ (IData)(__VdynTrigger_h621ad74f__0)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@([true] (32'sh0 < std::mailbox__Tz1.m_queue.size()))", 
                                                             "/usr/local/share/verilator/include/verilated_std.sv", 
                                                             63);
                __Vtrigcurrexpr_h63d4b802__0 = VL_LTS_III(32, 0U, this->__PVT__m_queue.size());
                __VdynTrigger_h621ad74f__0 = __Vtrigcurrexpr_h63d4b802__0;
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h621ad74f__0);
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@([true] (32'sh0 < std::mailbox__Tz1.m_queue.size()))", 
                                                         "/usr/local/share/verilator/include/verilated_std.sv", 
                                                         63);
        }
    }
    message = this->__PVT__m_queue.pop_front();
}

VlCoroutine Vtbench_top_std__03a__03amailbox__Tz1::__VnoInFunc_peek(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> &message) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03amailbox__Tz1::__VnoInFunc_peek\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    while ((0U == this->__PVT__m_queue.size())) {
        if (VL_GTES_III(32, 0U, this->__PVT__m_queue.size())) {
            CData/*0:0*/ __VdynTrigger_h621ad74f__1;
            __VdynTrigger_h621ad74f__1 = 0;
            __VdynTrigger_h621ad74f__1 = 0U;
            CData/*0:0*/ __Vtrigcurrexpr_h63d4b802__1;
            __Vtrigcurrexpr_h63d4b802__1 = 0;
            while ((1U & (~ (IData)(__VdynTrigger_h621ad74f__1)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@([true] (32'sh0 < std::mailbox__Tz1.m_queue.size()))", 
                                                             "/usr/local/share/verilator/include/verilated_std.sv", 
                                                             80);
                __Vtrigcurrexpr_h63d4b802__1 = VL_LTS_III(32, 0U, this->__PVT__m_queue.size());
                __VdynTrigger_h621ad74f__1 = __Vtrigcurrexpr_h63d4b802__1;
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h621ad74f__1);
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@([true] (32'sh0 < std::mailbox__Tz1.m_queue.size()))", 
                                                         "/usr/local/share/verilator/include/verilated_std.sv", 
                                                         80);
        }
    }
    message = this->__PVT__m_queue.at(0U);
}

void Vtbench_top_std__03a__03amailbox__Tz1::_ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03amailbox__Tz1::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
    __PVT__m_bound = 0;
    }
