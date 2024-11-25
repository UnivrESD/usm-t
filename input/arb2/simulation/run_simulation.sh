vlib work
vlog ../design/arb2.v ../design/arb2_tb.v
vsim -c -voptargs="+acc" -do "vcd file ../traces/t1.vcd; vcd add /*; run -all; vcd flush; quit" work.arb2_tb
rm -rf work

