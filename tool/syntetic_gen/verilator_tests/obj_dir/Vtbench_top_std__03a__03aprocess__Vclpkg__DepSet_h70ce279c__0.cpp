// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top_std__03a__03aprocess__Vclpkg.h"

void Vtbench_top_std__03a__03aprocess__Vclpkg::__VnoInFunc_self(VlProcessRef vlProcess, Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top_std__03a__03aprocess> &self__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vtbench_top_std__03a__03aprocess__Vclpkg::__VnoInFunc_self\n"); );
    // Body
    VlClassRef<Vtbench_top_std__03a__03aprocess> p;
    p = VL_NEW(Vtbench_top_std__03a__03aprocess, vlSymsp);
    // $c statement at /usr/local/share/verilator/include/verilated_std.sv:141:10
    VL_NULL_CHECK(p, "/usr/local/share/verilator/include/verilated_std.sv", 141)->__PVT__m_process = vlProcess;
    self__Vfuncrtn = p;
}

void Vtbench_top_std__03a__03aprocess::__VnoInFunc_suspend(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03aprocess::__VnoInFunc_suspend\n"); );
    // Body
    VL_WRITEF_NX("[%0t] %%Error: verilated_std.sv:165: Assertion failed in %Nstd.process.suspend: std::process::suspend() not supported\n",0,
                 64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name());
    VL_STOP_MT("/usr/local/share/verilator/include/verilated_std.sv", 165, "");
}

VlCoroutine Vtbench_top_std__03a__03aprocess::__VnoInFunc_await(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03aprocess::__VnoInFunc_await\n"); );
    // Init
    VL_KEEP_THIS;
    IData/*31:0*/ __Vfunc_status__2__Vfuncout;
    __Vfunc_status__2__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_status__3__Vfuncout;
    __Vfunc_status__3__Vfuncout = 0;
    // Body
    if ((1U & (~ ((0U == ([&]() {
                                this->__VnoInFunc_status(vlSymsp, __Vfunc_status__2__Vfuncout);
                            }(), __Vfunc_status__2__Vfuncout)) 
                  | (4U == ([&]() {
                                this->__VnoInFunc_status(vlSymsp, __Vfunc_status__3__Vfuncout);
                            }(), __Vfunc_status__3__Vfuncout)))))) {
        CData/*0:0*/ __VdynTrigger_h2e8a8623__0;
        __VdynTrigger_h2e8a8623__0 = 0;
        __VdynTrigger_h2e8a8623__0 = 0U;
        CData/*0:0*/ __Vtrigcurrexpr_h1865680e__0;
        __Vtrigcurrexpr_h1865680e__0 = 0;
        while ((1U & (~ (IData)(__VdynTrigger_h2e8a8623__0)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@([true] ((32'h0 == $_EXPRSTMT( // Function: status __VnoInFunc_status(std::process.__Vfunc_status__2__Vfuncout); , ); ) | (32'h4 == $_EXPRSTMT( // Function: status __VnoInFunc_status(std::process.__Vfunc_status__3__Vfuncout); , ); )))", 
                                                         "/usr/local/share/verilator/include/verilated_std.sv", 
                                                         174);
            __Vtrigcurrexpr_h1865680e__0 = ((0U == 
                                             ([&]() {
                            this->__VnoInFunc_status(vlSymsp, __Vfunc_status__2__Vfuncout);
                        }(), __Vfunc_status__2__Vfuncout)) 
                                            | (4U == 
                                               ([&]() {
                            this->__VnoInFunc_status(vlSymsp, __Vfunc_status__3__Vfuncout);
                        }(), __Vfunc_status__3__Vfuncout)));
            __VdynTrigger_h2e8a8623__0 = __Vtrigcurrexpr_h1865680e__0;
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h2e8a8623__0);
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@([true] ((32'h0 == $_EXPRSTMT( // Function: status __VnoInFunc_status(std::process.__Vfunc_status__2__Vfuncout); , ); ) | (32'h4 == $_EXPRSTMT( // Function: status __VnoInFunc_status(std::process.__Vfunc_status__3__Vfuncout); , ); )))", 
                                                     "/usr/local/share/verilator/include/verilated_std.sv", 
                                                     174);
    }
}

Vtbench_top_std__03a__03aprocess::Vtbench_top_std__03a__03aprocess(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03aprocess::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
}

void Vtbench_top_std__03a__03aprocess::_ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtbench_top_std__03a__03aprocess::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
    }
