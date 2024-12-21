MODULE=test

# Collect all Verilog files
VERILOG_FILES=$(wildcard spec*.v)

.PHONY: sim
sim: trace.vcd

.PHONY: verilate
verilate: .stamp.verilate

.PHONY: build
build: obj_dir/V$(MODULE)

.PHONY: waves
waves: trace.vcd
	@echo
	@echo "### WAVES ###"
	gtkwave trace.vcd

trace.vcd: ./obj_dir/V$(MODULE)
	@echo
	@echo "### SIMULATING ###"
	@./obj_dir/V$(MODULE)

./obj_dir/V$(MODULE): .stamp.verilate
	@echo
	@echo "### BUILDING SIM ###"
	make -C obj_dir -f V$(MODULE).mk V$(MODULE)

.stamp.verilate: $(VERILOG_FILES) tb_$(MODULE).cpp
	@echo
	@echo "### VERILATING ###"
	verilator -Wall --trace -cc $(MODULE).v $(VERILOG_FILES) --exe tb_$(MODULE).cpp
	@touch .stamp.verilate

.PHONY: lint
lint: $(VERILOG_FILES)
	verilator --lint-only $(VERILOG_FILES)

.PHONY: clean
clean:
	rm -rf .stamp.*
	rm -rf ./obj_dir
	rm -rf trace.vcd
