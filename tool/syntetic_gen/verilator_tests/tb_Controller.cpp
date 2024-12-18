#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VController.h"

#define MAX_SIM_TIME 20
vluint64_t sim_time = 0;

int main(int argc, char** argv, char** env) {
    VController *dut = new VController;

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("trace.vcd");

    while (sim_time < MAX_SIM_TIME) {
        dut->clock ^= 1;
        dut->a_0 = rand() % 2;
        dut->a_1 = rand() % 2;
        dut->a_2 = rand() % 2;
        dut->a_3 = rand() % 2;
        //dut->a_4 = rand() % 2;
        dut->eval();
        m_trace->dump(sim_time);
        sim_time++;
    }

    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}
