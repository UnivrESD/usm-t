 #!/bin/sh
rm -rf work
vlib work
vlog +incdir+tb/ tb/tb_fifo.v rtl/*.v
vsim -voptargs=+acc -c work.tb_fifo -do "run -all; exit" 
gtkwave tb_fifo.vcd
