// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtbench_top__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vtbench_top::Vtbench_top(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtbench_top__Syms(contextp(), _vcname__, this)}
    , __PVT____024unit{vlSymsp->TOP.__PVT____024unit}
    , __PVT__std{vlSymsp->TOP.__PVT__std}
    , __PVT__tbench_top__DOT__intf{vlSymsp->TOP.__PVT__tbench_top__DOT__intf}
    , __PVT__tbench_top__DOT__t1{vlSymsp->TOP.__PVT__tbench_top__DOT__t1}
    , __024unit__03a__03atransaction__Vclpkg{vlSymsp->TOP.__024unit__03a__03atransaction__Vclpkg}
    , __024unit__03a__03agenerator__Vclpkg{vlSymsp->TOP.__024unit__03a__03agenerator__Vclpkg}
    , __024unit__03a__03adriver__Vclpkg{vlSymsp->TOP.__024unit__03a__03adriver__Vclpkg}
    , __024unit__03a__03aenvironment__Vclpkg{vlSymsp->TOP.__024unit__03a__03aenvironment__Vclpkg}
    , test__03a__03amy_trans__Vclpkg{vlSymsp->TOP.test__03a__03amy_trans__Vclpkg}
    , std__03a__03asemaphore__Vclpkg{vlSymsp->TOP.std__03a__03asemaphore__Vclpkg}
    , std__03a__03aprocess__Vclpkg{vlSymsp->TOP.std__03a__03aprocess__Vclpkg}
    , std__03a__03amailbox__Tz1__Vclpkg{vlSymsp->TOP.std__03a__03amailbox__Tz1__Vclpkg}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vtbench_top::Vtbench_top(const char* _vcname__)
    : Vtbench_top(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtbench_top::~Vtbench_top() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtbench_top___024root___eval_debug_assertions(Vtbench_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vtbench_top___024root___eval_static(Vtbench_top___024root* vlSelf);
void Vtbench_top___024root___eval_initial(Vtbench_top___024root* vlSelf);
void Vtbench_top___024root___eval_settle(Vtbench_top___024root* vlSelf);
void Vtbench_top___024root___eval(Vtbench_top___024root* vlSelf);

void Vtbench_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtbench_top::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtbench_top___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->clearTriggeredEvents();
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtbench_top___024root___eval_static(&(vlSymsp->TOP));
        Vtbench_top___024root___eval_initial(&(vlSymsp->TOP));
        Vtbench_top___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtbench_top___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

void Vtbench_top::eval_end_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+eval_end_step Vtbench_top::eval_end_step\n"); );
#ifdef VM_TRACE
    // Tracing
    if (VL_UNLIKELY(vlSymsp->__Vm_dumping)) vlSymsp->_traceDump();
#endif  // VM_TRACE
}

//============================================================
// Events and timing
bool Vtbench_top::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vtbench_top::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtbench_top::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtbench_top___024root___eval_final(Vtbench_top___024root* vlSelf);

VL_ATTR_COLD void Vtbench_top::final() {
    Vtbench_top___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtbench_top::hierName() const { return vlSymsp->name(); }
const char* Vtbench_top::modelName() const { return "Vtbench_top"; }
unsigned Vtbench_top::threads() const { return 1; }
void Vtbench_top::prepareClone() const { contextp()->prepareClone(); }
void Vtbench_top::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vtbench_top::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vtbench_top___024root__trace_decl_types(VerilatedVcd* tracep);

void Vtbench_top___024root__trace_init_top(Vtbench_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vtbench_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtbench_top___024root*>(voidSelf);
    Vtbench_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vtbench_top___024root__trace_decl_types(tracep);
    Vtbench_top___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtbench_top___024root__trace_register(Vtbench_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vtbench_top::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vtbench_top::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vtbench_top___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
