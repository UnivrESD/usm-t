// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP___024UNIT__03A__03ATRANSACTION__VCLPKG_H_
#define VERILATED_VTBENCH_TOP___024UNIT__03A__03ATRANSACTION__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"
class Vtbench_top___024unit__03a__03atransaction;


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top___024unit__03a__03atransaction__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top___024unit__03a__03atransaction__Vclpkg(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top___024unit__03a__03atransaction__Vclpkg();
    VL_UNCOPYABLE(Vtbench_top___024unit__03a__03atransaction__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


class Vtbench_top__Syms;

class Vtbench_top___024unit__03a__03atransaction : public VlClass {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __PVT__a_0;
    CData/*0:0*/ __PVT__a_1;
    CData/*0:0*/ __PVT__a_2;
    CData/*0:0*/ __PVT__a_3;
    CData/*0:0*/ __PVT__a_4;
    VlQueue<CData/*0:0*/> __Vrandmode;

    // INTERNAL VARIABLES
    VlRNG __Vm_rng;
    virtual void __VnoInFunc___Vbasic_randomize(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &__Vbasic_randomize__Vfuncrtn);
    void __VnoInFunc_do_copy(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> &do_copy__Vfuncrtn);
    void __VnoInFunc_post_randomize(Vtbench_top__Syms* __restrict vlSymsp);
    virtual void __VnoInFunc_randomize(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &randomize__Vfuncrtn);
  private:
    void _ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp);
  public:
    Vtbench_top___024unit__03a__03atransaction(Vtbench_top__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    virtual ~Vtbench_top___024unit__03a__03atransaction();
};

std::string VL_TO_STRING(const VlClassRef<Vtbench_top___024unit__03a__03atransaction>& obj);

#endif  // guard
