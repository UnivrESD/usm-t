// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VController__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

VController::VController(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VController__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , a_1{vlSymsp->TOP.a_1}
    , a_2{vlSymsp->TOP.a_2}
    , a_3{vlSymsp->TOP.a_3}
    , c_0{vlSymsp->TOP.c_0}
    , c_1{vlSymsp->TOP.c_1}
    , c_2{vlSymsp->TOP.c_2}
    , c_3{vlSymsp->TOP.c_3}
    , a_0{vlSymsp->TOP.a_0}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

VController::VController(const char* _vcname__)
    : VController(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VController::~VController() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VController___024root___eval_debug_assertions(VController___024root* vlSelf);
#endif  // VL_DEBUG
void VController___024root___eval_static(VController___024root* vlSelf);
void VController___024root___eval_initial(VController___024root* vlSelf);
void VController___024root___eval_settle(VController___024root* vlSelf);
void VController___024root___eval(VController___024root* vlSelf);

void VController::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VController::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VController___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VController___024root___eval_static(&(vlSymsp->TOP));
        VController___024root___eval_initial(&(vlSymsp->TOP));
        VController___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VController___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VController::eventsPending() { return false; }

uint64_t VController::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VController::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VController___024root___eval_final(VController___024root* vlSelf);

VL_ATTR_COLD void VController::final() {
    VController___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VController::hierName() const { return vlSymsp->name(); }
const char* VController::modelName() const { return "VController"; }
unsigned VController::threads() const { return 1; }
void VController::prepareClone() const { contextp()->prepareClone(); }
void VController::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> VController::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void VController___024root__trace_decl_types(VerilatedVcd* tracep);

void VController___024root__trace_init_top(VController___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    VController___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VController___024root*>(voidSelf);
    VController__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    VController___024root__trace_decl_types(tracep);
    VController___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void VController___024root__trace_register(VController___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void VController::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'VController::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    VController___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
