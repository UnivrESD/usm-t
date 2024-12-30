python3 ../src3/goldmine.py -m arb2 -u /input/ -S -V -f /input/ --clock clk:1 --vcd /input/bool/t1.vcd 
find goldmine.out/ -name "*.gold" -exec cat {} + > /output/$MINED_ASSERTIONS_FILE
