// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtbench_top.h for the primary calling header

#ifndef VERILATED_VTBENCH_TOP_TEST__03A__03AMY_TRANS__VCLPKG_H_
#define VERILATED_VTBENCH_TOP_TEST__03A__03AMY_TRANS__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
#include "verilated_random.h"
class Vtbench_top___024unit__03a__03atransaction;


class Vtbench_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtbench_top_test__03a__03amy_trans__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vtbench_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtbench_top_test__03a__03amy_trans__Vclpkg(Vtbench_top__Syms* symsp, const char* v__name);
    ~Vtbench_top_test__03a__03amy_trans__Vclpkg();
    VL_UNCOPYABLE(Vtbench_top_test__03a__03amy_trans__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"

class Vtbench_top__Syms;

class Vtbench_top_test__03a__03amy_trans : public Vtbench_top___024unit__03a__03atransaction {
  public:
    virtual void __VnoInFunc___Vbasic_randomize(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &__Vbasic_randomize__Vfuncrtn);
    void __VnoInFunc_pre_randomize(Vtbench_top__Syms* __restrict vlSymsp);
    virtual void __VnoInFunc_randomize(Vtbench_top__Syms* __restrict vlSymsp, IData/*31:0*/ &randomize__Vfuncrtn);
  private:
    void _ctor_var_reset(Vtbench_top__Syms* __restrict vlSymsp);
  public:
    Vtbench_top_test__03a__03amy_trans(Vtbench_top__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    virtual ~Vtbench_top_test__03a__03amy_trans();
};

std::string VL_TO_STRING(const VlClassRef<Vtbench_top_test__03a__03amy_trans>& obj);

#endif  // guard
