// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtbench_top__pch.h"
#include "Vtbench_top.h"
#include "Vtbench_top___024root.h"
#include "Vtbench_top___024unit.h"
#include "Vtbench_top_test.h"
#include "Vtbench_top_std.h"
#include "Vtbench_top_controller_intf.h"
#include "Vtbench_top___024unit__03a__03atransaction__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03agenerator__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03adriver__Vclpkg.h"
#include "Vtbench_top___024unit__03a__03aenvironment__Vclpkg.h"
#include "Vtbench_top_test__03a__03amy_trans__Vclpkg.h"
#include "Vtbench_top_std__03a__03asemaphore__Vclpkg.h"
#include "Vtbench_top_std__03a__03aprocess__Vclpkg.h"
#include "Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg.h"

// FUNCTIONS
Vtbench_top__Syms::~Vtbench_top__Syms()
{
#ifdef VM_TRACE
    if (__Vm_dumping) _traceDumpClose();
#endif  // VM_TRACE
}

void Vtbench_top__Syms::_traceDump() {
    const VerilatedLockGuard lock(__Vm_dumperMutex);
    __Vm_dumperp->dump(VL_TIME_Q());
}

void Vtbench_top__Syms::_traceDumpOpen() {
    const VerilatedLockGuard lock(__Vm_dumperMutex);
    if (VL_UNLIKELY(!__Vm_dumperp)) {
        __Vm_dumperp = new VerilatedVcdC();
        __Vm_modelp->trace(__Vm_dumperp, 0, 0);
        std::string dumpfile = _vm_contextp__->dumpfileCheck();
        __Vm_dumperp->open(dumpfile.c_str());
        __Vm_dumping = true;
    }
}

void Vtbench_top__Syms::_traceDumpClose() {
    const VerilatedLockGuard lock(__Vm_dumperMutex);
    __Vm_dumping = false;
    VL_DO_CLEAR(delete __Vm_dumperp, __Vm_dumperp = nullptr);
}

Vtbench_top__Syms::Vtbench_top__Syms(VerilatedContext* contextp, const char* namep, Vtbench_top* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
    , TOP____024unit__03a__03adriver__Vclpkg{this, Verilated::catName(namep, "$unit::driver__Vclpkg")}
    , TOP____024unit__03a__03aenvironment__Vclpkg{this, Verilated::catName(namep, "$unit::environment__Vclpkg")}
    , TOP____024unit__03a__03agenerator__Vclpkg{this, Verilated::catName(namep, "$unit::generator__Vclpkg")}
    , TOP____024unit__03a__03atransaction__Vclpkg{this, Verilated::catName(namep, "$unit::transaction__Vclpkg")}
    , TOP____024unit{this, Verilated::catName(namep, "$unit")}
    , TOP__std{this, Verilated::catName(namep, "std")}
    , TOP__tbench_top__DOT__intf{this, Verilated::catName(namep, "tbench_top.intf")}
    , TOP__tbench_top__DOT__t1{this, Verilated::catName(namep, "tbench_top.t1")}
    , TOP__std__03a__03amailbox__Tz1__Vclpkg{this, Verilated::catName(namep, "std::mailbox__Tz1__Vclpkg")}
    , TOP__std__03a__03aprocess__Vclpkg{this, Verilated::catName(namep, "std::process__Vclpkg")}
    , TOP__std__03a__03asemaphore__Vclpkg{this, Verilated::catName(namep, "std::semaphore__Vclpkg")}
    , TOP__test__03a__03amy_trans__Vclpkg{this, Verilated::catName(namep, "test::my_trans__Vclpkg")}
{
        // Check resources
        Verilated::stackCheck(283);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.__024unit__03a__03adriver__Vclpkg = &TOP____024unit__03a__03adriver__Vclpkg;
    TOP.__024unit__03a__03aenvironment__Vclpkg = &TOP____024unit__03a__03aenvironment__Vclpkg;
    TOP.__024unit__03a__03agenerator__Vclpkg = &TOP____024unit__03a__03agenerator__Vclpkg;
    TOP.__024unit__03a__03atransaction__Vclpkg = &TOP____024unit__03a__03atransaction__Vclpkg;
    TOP.__PVT____024unit = &TOP____024unit;
    TOP.__PVT__std = &TOP__std;
    TOP.__PVT__tbench_top__DOT__intf = &TOP__tbench_top__DOT__intf;
    TOP.__PVT__tbench_top__DOT__t1 = &TOP__tbench_top__DOT__t1;
    TOP.std__03a__03amailbox__Tz1__Vclpkg = &TOP__std__03a__03amailbox__Tz1__Vclpkg;
    TOP.std__03a__03aprocess__Vclpkg = &TOP__std__03a__03aprocess__Vclpkg;
    TOP.std__03a__03asemaphore__Vclpkg = &TOP__std__03a__03asemaphore__Vclpkg;
    TOP.test__03a__03amy_trans__Vclpkg = &TOP__test__03a__03amy_trans__Vclpkg;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP____024unit__03a__03adriver__Vclpkg.__Vconfigure(true);
    TOP____024unit__03a__03aenvironment__Vclpkg.__Vconfigure(true);
    TOP____024unit__03a__03agenerator__Vclpkg.__Vconfigure(true);
    TOP____024unit__03a__03atransaction__Vclpkg.__Vconfigure(true);
    TOP____024unit.__Vconfigure(true);
    TOP__std.__Vconfigure(true);
    TOP__tbench_top__DOT__intf.__Vconfigure(true);
    TOP__tbench_top__DOT__t1.__Vconfigure(true);
    TOP__std__03a__03amailbox__Tz1__Vclpkg.__Vconfigure(true);
    TOP__std__03a__03aprocess__Vclpkg.__Vconfigure(true);
    TOP__std__03a__03asemaphore__Vclpkg.__Vconfigure(true);
    TOP__test__03a__03amy_trans__Vclpkg.__Vconfigure(true);
    // Setup scopes
    __Vscope___024unit__generator.configure(this, name(), "$unit.generator", "generator", "<null>", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope___024unit__generator__main__unnamedblk1_1.configure(this, name(), "$unit.generator.main.unnamedblk1_1", "unnamedblk1_1", "<null>", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope_std__process.configure(this, name(), "std.process", "process", "<null>", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope_std__process__suspend.configure(this, name(), "std.process.suspend", "suspend", "<null>", -12, VerilatedScope::SCOPE_OTHER);
}
