#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtest.h"

#define MAX_SIM_TIME 1000
vluint64_t sim_time = 0;

int main(int argc, char** argv, char** env) {
    Vtest *dut = new Vtest;

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("trace.vcd");
    int state = 0;

    dut->clock ^= 1;
    dut->eval();
    m_trace->dump(sim_time);
    sim_time++;
    dut->clock ^= 1;
    dut->eval();
    m_trace->dump(sim_time);
    sim_time++;
    while (sim_time < MAX_SIM_TIME) {

        dut->clock ^= 1;
        // dut->a_0 = 1;
        // dut->a_1 = 1;
        // dut->a_2 ^= 1;
        // dut->a_3 ^= 1;
        dut->a_1_0 = rand() % 2;
		dut->a_1_1 = rand() % 2;
		dut->a_2_0 = rand() % 2;
		dut->a_2_1 = rand() % 2;
		

        dut->eval();
        m_trace->dump(sim_time);
        sim_time++;

    }

    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}
