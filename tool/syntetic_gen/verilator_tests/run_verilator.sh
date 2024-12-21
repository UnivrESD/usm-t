files=$(ls | grep -v 'test.v')

verilator -Wall --trace -cc test.v --exe tb_test.cpp && make -C obj_dir -f Vtest.mk Vtest