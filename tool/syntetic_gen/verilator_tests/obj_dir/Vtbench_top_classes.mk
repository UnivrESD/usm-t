# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Make include file with class lists
#
# This file lists generated Verilated files, for including in higher level makefiles.
# See Vtbench_top.mk for the caller.

### Switches...
# C11 constructs required?  0/1 (always on now)
VM_C11 = 1
# Timing enabled?  0/1
VM_TIMING = 1
# Coverage output mode?  0/1 (from --coverage)
VM_COVERAGE = 0
# Parallel builds?  0/1 (from --output-split)
VM_PARALLEL_BUILDS = 0
# Tracing output mode?  0/1 (from --trace/--trace-fst)
VM_TRACE = 1
# Tracing output mode in VCD format?  0/1 (from --trace)
VM_TRACE_VCD = 1
# Tracing output mode in FST format?  0/1 (from --trace-fst)
VM_TRACE_FST = 0

### Object file lists...
# Generated module classes, fast-path, compile with highest optimization
VM_CLASSES_FAST += \
	Vtbench_top \
	Vtbench_top___024root__DepSet_h65e1282e__0 \
	Vtbench_top___024root__DepSet_h3855b66f__0 \
	Vtbench_top_test__DepSet_h71758616__0 \
	Vtbench_top_controller_intf__DepSet_h572c9934__0 \
	Vtbench_top___024unit__03a__03atransaction__Vclpkg__DepSet_h1900d410__0 \
	Vtbench_top___024unit__03a__03atransaction__Vclpkg__DepSet_h94350a51__0 \
	Vtbench_top___024unit__03a__03agenerator__Vclpkg__DepSet_h5a750c6b__0 \
	Vtbench_top___024unit__03a__03agenerator__Vclpkg__DepSet_h12606440__0 \
	Vtbench_top___024unit__03a__03agenerator__Vclpkg__DepSet_h0fca8f71__0 \
	Vtbench_top___024unit__03a__03agenerator__Vclpkg__DepSet_h54c9d2aa__0 \
	Vtbench_top___024unit__03a__03adriver__Vclpkg__DepSet_h5318ca16__0 \
	Vtbench_top___024unit__03a__03adriver__Vclpkg__DepSet_ha17c1c71__0 \
	Vtbench_top___024unit__03a__03adriver__Vclpkg__DepSet_h4e2d1457__0 \
	Vtbench_top___024unit__03a__03aenvironment__Vclpkg__DepSet_hc11bd4a1__0 \
	Vtbench_top___024unit__03a__03aenvironment__Vclpkg__DepSet_h392e0b28__0 \
	Vtbench_top___024unit__03a__03aenvironment__Vclpkg__DepSet_he32ac06b__0 \
	Vtbench_top___024unit__03a__03aenvironment__Vclpkg__DepSet_h12c26d28__0 \
	Vtbench_top___024unit__03a__03aenvironment__Vclpkg__DepSet_hbe1f1eaa__0 \
	Vtbench_top___024unit__03a__03aenvironment__Vclpkg__DepSet_hb2065a7e__0 \
	Vtbench_top_test__03a__03amy_trans__Vclpkg__DepSet_haba07485__0 \
	Vtbench_top_test__03a__03amy_trans__Vclpkg__DepSet_h31177950__0 \
	Vtbench_top_test__03a__03amy_trans__Vclpkg__DepSet_h0a4e3434__0 \
	Vtbench_top_test__03a__03amy_trans__Vclpkg__DepSet_h6c2b6791__0 \
	Vtbench_top_std__03a__03asemaphore__Vclpkg__DepSet_ha119c8ec__0 \
	Vtbench_top_std__03a__03asemaphore__Vclpkg__DepSet_hfc2e172d__0 \
	Vtbench_top_std__03a__03aprocess__Vclpkg__DepSet_h70ce279c__0 \
	Vtbench_top_std__03a__03aprocess__Vclpkg__DepSet_h2b82b9dd__0 \
	Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg__DepSet_h2e451fe0__0 \
	Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg__DepSet_h80f9c221__0 \
	Vtbench_top__main \

# Generated module classes, non-fast-path, compile with low/medium optimization
VM_CLASSES_SLOW += \
	Vtbench_top___024root__Slow \
	Vtbench_top___024root__DepSet_h65e1282e__0__Slow \
	Vtbench_top___024root__DepSet_h3855b66f__0__Slow \
	Vtbench_top___024unit__Slow \
	Vtbench_top___024unit__DepSet_hf6c660cc__0__Slow \
	Vtbench_top_test__Slow \
	Vtbench_top_test__DepSet_h1fde50b0__0__Slow \
	Vtbench_top_std__Slow \
	Vtbench_top_std__DepSet_hb75a4de8__0__Slow \
	Vtbench_top_controller_intf__Slow \
	Vtbench_top_controller_intf__DepSet_h572c9934__0__Slow \
	Vtbench_top___024unit__03a__03atransaction__Vclpkg__Slow \
	Vtbench_top___024unit__03a__03atransaction__Vclpkg__DepSet_h94350a51__0__Slow \
	Vtbench_top___024unit__03a__03agenerator__Vclpkg__Slow \
	Vtbench_top___024unit__03a__03agenerator__Vclpkg__DepSet_h54c9d2aa__0__Slow \
	Vtbench_top___024unit__03a__03adriver__Vclpkg__Slow \
	Vtbench_top___024unit__03a__03adriver__Vclpkg__DepSet_h4e2d1457__0__Slow \
	Vtbench_top___024unit__03a__03aenvironment__Vclpkg__Slow \
	Vtbench_top___024unit__03a__03aenvironment__Vclpkg__DepSet_hbe1f1eaa__0__Slow \
	Vtbench_top_test__03a__03amy_trans__Vclpkg__Slow \
	Vtbench_top_test__03a__03amy_trans__Vclpkg__DepSet_h6c2b6791__0__Slow \
	Vtbench_top_std__03a__03asemaphore__Vclpkg__Slow \
	Vtbench_top_std__03a__03asemaphore__Vclpkg__DepSet_hfc2e172d__0__Slow \
	Vtbench_top_std__03a__03aprocess__Vclpkg__Slow \
	Vtbench_top_std__03a__03aprocess__Vclpkg__DepSet_h2b82b9dd__0__Slow \
	Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg__Slow \
	Vtbench_top_std__03a__03amailbox__Tz1__Vclpkg__DepSet_h80f9c221__0__Slow \

# Generated support classes, fast-path, compile with highest optimization
VM_SUPPORT_FAST += \
	Vtbench_top__Trace__0 \

# Generated support classes, non-fast-path, compile with low/medium optimization
VM_SUPPORT_SLOW += \
	Vtbench_top__Syms \
	Vtbench_top__Trace__0__Slow \
	Vtbench_top__TraceDecls__0__Slow \

# Global classes, need linked once per executable, fast-path, compile with highest optimization
VM_GLOBAL_FAST += \
	verilated \
	verilated_vcd_c \
	verilated_timing \
	verilated_random \
	verilated_threads \

# Global classes, need linked once per executable, non-fast-path, compile with low/medium optimization
VM_GLOBAL_SLOW += \


# Verilated -*- Makefile -*-
