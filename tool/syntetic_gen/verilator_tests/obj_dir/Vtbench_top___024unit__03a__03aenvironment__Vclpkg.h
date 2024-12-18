// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP___024UNIT__03A__03AENVIRONMENT__VCLPKG_H_
#define VERILATED_VTBENCH_TOP___024UNIT__03A__03AENVIRONMENT__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"
class Vtbench_top___024unit__03a__03adriver;
class Vtbench_top___024unit__03a__03agenerator;
class Vtbench_top_std__03a__03amailbox__Tz1;


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top___024unit__03a__03aenvironment__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top___024unit__03a__03aenvironment__Vclpkg(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top___024unit__03a__03aenvironment__Vclpkg();
    VL_UNCOPYABLE(Vtbench_top___024unit__03a__03aenvironment__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


class Vtbench_top__Syms;

class Vtbench_top___024unit__03a__03aenvironment : public VlClass {
  public:

    // DESIGN SPECIFIC STATE
    VlAssignableEvent __PVT__gen_ended;
    VlClassRef<Vtbench_top___024unit__03a__03agenerator> __PVT__gen;
    VlClassRef<Vtbench_top___024unit__03a__03adriver> __PVT__driv;
    VlClassRef<Vtbench_top_std__03a__03amailbox__Tz1> __PVT__gen2driv;
    Vtbench_top_controller_intf* __PVT__controller_vif;
    VlCoroutine __VnoInFunc_post_test(Vtbench_top__Syms* __restrict vlSymsp);
    void __VnoInFunc_pre_test(Vtbench_top__Syms* __restrict vlSymsp);
    VlCoroutine __VnoInFunc_run(Vtbench_top__Syms* __restrict vlSymsp);
    void __VnoInFunc_test(Vtbench_top__Syms* __restrict vlSymsp);
  private:
    VlCoroutine __VnoInFunc_test____Vfork_1__0(Vtbench_top__Syms* __restrict vlSymsp);
    VlCoroutine __VnoInFunc_test____Vfork_1__1(Vtbench_top__Syms* __restrict vlSymsp);
    void _ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp);
  public:
    Vtbench_top___024unit__03a__03aenvironment(Vtbench_top__Syms* __restrict vlSymsp, Vtbench_top_controller_intf* controller_vif);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vtbench_top___024unit__03a__03aenvironment();
};

std::string VL_TO_STRING(const VlClassRef<Vtbench_top___024unit__03a__03aenvironment>& obj);

#endif  // guard
