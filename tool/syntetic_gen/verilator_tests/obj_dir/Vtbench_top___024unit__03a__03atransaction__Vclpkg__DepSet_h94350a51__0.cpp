// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"

void Vtbench_top___024unit__03a__03atransaction::__VnoInFunc_post_randomize(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::__VnoInFunc_post_randomize\n"); );
    // Body
    VL_WRITEF_NX("--------- [Trans] post_randomize ------\n\t a_0 = %0x\n\t a_1 = %0x\n\t a_2 = %0x\n\t a_3 = %0x\n\t a_4 = %0x\n-----------------------------------------\n",0,
                 1,this->__PVT__a_0,1,(IData)(this->__PVT__a_1),
                 1,this->__PVT__a_2,1,(IData)(this->__PVT__a_3),
                 1,this->__PVT__a_4);
}

void Vtbench_top___024unit__03a__03atransaction::__VnoInFunc_randomize(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &randomize__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::__VnoInFunc_randomize\n"); );
    // Init
    IData/*31:0*/ __Vfunc___Vbasic_randomize__1__Vfuncout;
    __Vfunc___Vbasic_randomize__1__Vfuncout = 0;
    // Body
    randomize__Vfuncrtn = 1U;
    randomize__Vfuncrtn = (1U & ([&]() {
                this->__VnoInFunc___Vbasic_randomize(vlSymsp, __Vfunc___Vbasic_randomize__1__Vfuncout);
            }(), __Vfunc___Vbasic_randomize__1__Vfuncout));
    this->__VnoInFunc_post_randomize(vlSymsp);
}

void Vtbench_top___024unit__03a__03atransaction::__VnoInFunc___Vbasic_randomize(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &__Vbasic_randomize__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::__VnoInFunc___Vbasic_randomize\n"); );
    // Body
    __Vbasic_randomize__Vfuncrtn = 1U;
    if (this->__Vrandmode.at(0U)) {
        this->__PVT__a_0 = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
    if (this->__Vrandmode.at(1U)) {
        this->__PVT__a_1 = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
    if (this->__Vrandmode.at(2U)) {
        this->__PVT__a_2 = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
    if (this->__Vrandmode.at(3U)) {
        this->__PVT__a_3 = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
    if (this->__Vrandmode.at(4U)) {
        this->__PVT__a_4 = (1U & VL_RANDOM_RNG_I(__Vm_rng));
    }
}

Vtbench_top___024unit__03a__03atransaction::~Vtbench_top___024unit__03a__03atransaction() {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vtbench_top___024unit__03a__03atransaction>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vtbench_top___024unit__03a__03atransaction::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vtbench_top___024unit__03a__03atransaction::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03atransaction::to_string_middle\n"); );
    // Body
    std::string out;
    out += "a_0:" + VL_TO_STRING(__PVT__a_0);
    out += ", a_1:" + VL_TO_STRING(__PVT__a_1);
    out += ", a_2:" + VL_TO_STRING(__PVT__a_2);
    out += ", a_3:" + VL_TO_STRING(__PVT__a_3);
    out += ", a_4:" + VL_TO_STRING(__PVT__a_4);
    out += ", __Vrandmode:" + VL_TO_STRING(__Vrandmode);
    return out;
}
