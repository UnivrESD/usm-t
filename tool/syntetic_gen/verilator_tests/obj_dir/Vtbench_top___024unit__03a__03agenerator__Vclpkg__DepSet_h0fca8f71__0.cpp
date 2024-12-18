// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtbench_top.h for the primary calling header

#include "Vtbench_top__pch.h"
#include "Vtbench_top__Syms.h"
#include "Vtbench_top___024unit__03a__03agenerator__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"
#include "Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg.h"

VlCoroutine Vtbench_top___024unit__03a__03agenerator::__VnoInFunc_main(Vtbench_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtbench_top___024unit__03a__03agenerator::__VnoInFunc_main\n"); );
    // Init
    VL_KEEP_THIS;
    IData/*31:0*/ __Vtask_randomize__1__Vfuncout;
    __Vtask_randomize__1__Vfuncout = 0;
    VlClassRef<Vtbench_top___024unit__03a__03atransaction> __Vtask_do_copy__2__Vfuncout;
    // Body
    IData/*31:0*/ unnamedblk1_1__DOT____Vrepeat0;
    unnamedblk1_1__DOT____Vrepeat0 = 0;
    unnamedblk1_1__DOT____Vrepeat0 = this->__PVT__repeat_count;
    while (VL_LTS_III(32, 0U, unnamedblk1_1__DOT____Vrepeat0)) {
        if (VL_UNLIKELY((1U != ([&]() {
                            VL_NULL_CHECK(this->__PVT__trans, "tb/generator.sv", 26)
                                ->__VnoInFunc_randomize(vlSymsp, __Vtask_randomize__1__Vfuncout);
                        }(), __Vtask_randomize__1__Vfuncout)))) {
            VL_WRITEF_NX("[%0t] %%Fatal: generator.sv:26: Assertion failed in %N$unit.generator.main.unnamedblk1_1\n",0,
                         64,VL_TIME_UNITED_Q(1),-12,
                         vlSymsp->name());
            VL_STOP_MT("tb/generator.sv", 26, "", false);
        }
        VL_NULL_CHECK(this->__PVT__trans, "tb/generator.sv", 27)->__VnoInFunc_do_copy(vlSymsp, __Vtask_do_copy__2__Vfuncout);
        this->__PVT__tr = __Vtask_do_copy__2__Vfuncout;
        co_await VL_NULL_CHECK(this->__PVT__gen2driv, "tb/generator.sv", 28)->__VnoInFunc_put(vlSymsp, this->__PVT__tr);
        unnamedblk1_1__DOT____Vrepeat0 = (unnamedblk1_1__DOT____Vrepeat0 
                                          - (IData)(1U));
    }
    vlSymsp->fireEvent(this->__PVT__ended);
}
