// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP_STD__03A__03AMAILBOX__TZ1__VCLPKG_H_
#define VERILATED_VTBENCH_TOP_STD__03A__03AMAILBOX__TZ1__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"
class Vtbench_top___024unit__03a__03atransaction;


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg();
    VL_UNCOPYABLE(Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


class Vtbench_top__Syms;

class Vtbench_top_std__03a__03amailbox__Tz1 : public VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT__m_bound;
    VlQueue<VlClassRef<Vtbench_top___024unit__03a__03atransaction>> __PVT__m_queue;
    VlCoroutine __VnoInFunc_get(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> &message);
    void __VnoInFunc_num(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &num__Vfuncrtn);
    VlCoroutine __VnoInFunc_peek(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> &message);
    VlCoroutine __VnoInFunc_put(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> message);
    void __VnoInFunc_try_get(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> &message, IData/*31:0*/ &try_get__Vfuncrtn);
    void __VnoInFunc_try_peek(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> &message, IData/*31:0*/ &try_peek__Vfuncrtn);
    void __VnoInFunc_try_put(Vtbench_top__Syms* __restrict vlSymsp, VlClassRef<Vtbench_top___024unit__03a__03atransaction> message, IData/*31:0*/ &try_put__Vfuncrtn);
  private:
    void _ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp);
  public:
    Vtbench_top_std__03a__03amailbox__Tz1(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ bound);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vtbench_top_std__03a__03amailbox__Tz1();
};

std::string VL_TO_STRING(const VlClassRef<Vtbench_top_std__03a__03amailbox__Tz1>& obj);

#endif  // guard
