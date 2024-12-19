#$bin/bash
touch test.aiger
ltlsynt --formula="G({a_0 ##1 a_1} |-> {c_0})" --ins="a_0,a_1" --outs="c_0,c_1"  --aiger > test.aiger
tail -n +2 test.aiger > temp.aiger && mv temp.aiger test.aiger

yosys -p 'read_aiger  -module_name test -clk_name clock ./test.aiger; write_verilog -sv ./test.sv'
make sim 
make waves 
