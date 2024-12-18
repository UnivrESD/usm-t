// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP___024UNIT__03A__03ADRIVER__VCLPKG_H_
#define VERILATED_VTBENCH_TOP___024UNIT__03A__03ADRIVER__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"
class Vtbench_top___024unit__03a__03atransaction;
class Vtbench_top_std__03a__03amailbox__Tz1;


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top___024unit__03a__03adriver__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top___024unit__03a__03adriver__Vclpkg(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top___024unit__03a__03adriver__Vclpkg();
    VL_UNCOPYABLE(Vtbench_top___024unit__03a__03adriver__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


class Vtbench_top__Syms;

class Vtbench_top___024unit__03a__03adriver : public VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT__no_transactions;
    Vtbench_top_controller_intf* __PVT__controller_vif;
    VlClassRef<Vtbench_top_std__03a__03amailbox__Tz1> __PVT__gen2driv;
    VlCoroutine __VnoInFunc_drive(Vtbench_top__Syms* __restrict vlSymsp);
    VlCoroutine __VnoInFunc_main(Vtbench_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp);
  public:
    Vtbench_top___024unit__03a__03adriver(Vtbench_top__Syms* __restrict vlSymsp, Vtbench_top_controller_intf* controller_vif, VlClassRef<Vtbench_top_std__03a__03amailbox__Tz1> gen2driv);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vtbench_top___024unit__03a__03adriver();
};

std::string VL_TO_STRING(const VlClassRef<Vtbench_top___024unit__03a__03adriver>& obj);

#endif  // guard
