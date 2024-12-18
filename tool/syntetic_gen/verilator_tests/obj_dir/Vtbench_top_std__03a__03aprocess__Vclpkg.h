// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP_STD__03A__03APROCESS__VCLPKG_H_
#define VERILATED_VTBENCH_TOP_STD__03A__03APROCESS__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"
class Vtbench_top_std__03a__03aprocess;


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top_std__03a__03aprocess__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top_std__03a__03aprocess__Vclpkg(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top_std__03a__03aprocess__Vclpkg();
    VL_UNCOPYABLE(Vtbench_top_std__03a__03aprocess__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __VnoInFunc_self(VlProcessRef vlProcess, Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top_std__03a__03aprocess> &self__Vfuncrtn);
};


class Vtbench_top__Syms;

class Vtbench_top_std__03a__03aprocess : public VlClass {
  public:

    // DESIGN SPECIFIC STATE
    VlProcessRef __PVT__m_process;
    VlCoroutine __VnoInFunc_await(Vtbench_top__Syms* __restrict vlSymsp);
    void __VnoInFunc_get_randstate(Vtbench_top__Syms* __restrict vlSymsp, std::string &get_randstate__Vfuncrtn);
    void __VnoInFunc_kill(Vtbench_top__Syms* __restrict vlSymsp);
    void __VnoInFunc_resume(Vtbench_top__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_randstate(Vtbench_top__Syms* __restrict vlSymsp, std::string s);
    void __VnoInFunc_set_status(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ s);
    void __VnoInFunc_status(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &status__Vfuncrtn);
    void __VnoInFunc_suspend(Vtbench_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp);
  public:
    Vtbench_top_std__03a__03aprocess(Vtbench_top__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vtbench_top_std__03a__03aprocess();
};

std::string VL_TO_STRING(const VlClassRef<Vtbench_top_std__03a__03aprocess>& obj);

#endif  // guard
