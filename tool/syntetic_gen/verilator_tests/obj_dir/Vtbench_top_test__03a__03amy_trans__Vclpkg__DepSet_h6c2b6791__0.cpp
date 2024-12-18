// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top_test__03a__03amy_trans__Vclpkg.h"

void Vtbench_top_test__03a__03amy_trans::__VnoInFunc_randomize(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &randomize__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top_test__03a__03amy_trans::__VnoInFunc_randomize\n"); );
    // Init
    IData/*31:0*/ __Vfunc___Vbasic_randomize__2__Vfuncout;
    __Vfunc___Vbasic_randomize__2__Vfuncout = 0;
    IData/*31:0*/ __Vtemp_1;
    // Body
    this->__VnoInFunc_pre_randomize(vlSymsp);
    randomize__Vfuncrtn = 1U;
    __Vtemp_1 = (randomize__Vfuncrtn & ([&]() {
                this->__VnoInFunc___Vbasic_randomize(vlSymsp, __Vfunc___Vbasic_randomize__2__Vfuncout);
            }(), __Vfunc___Vbasic_randomize__2__Vfuncout));
    randomize__Vfuncrtn = __Vtemp_1;
}

Vtbench_top_test__03a__03amy_trans::~Vtbench_top_test__03a__03amy_trans() {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top_test__03a__03amy_trans::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vtbench_top_test__03a__03amy_trans>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top_test__03a__03amy_trans::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vtbench_top_test__03a__03amy_trans::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top_test__03a__03amy_trans::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vtbench_top_test__03a__03amy_trans::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top_test__03a__03amy_trans::to_string_middle\n"); );
    // Body
    std::string out;
    out += Vtbench_top___024unit__03a__03atransaction::to_string_middle();
    return out;
}
