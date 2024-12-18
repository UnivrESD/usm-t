#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtest.h"

#define DEBUG true

#define MAX_SIM_TIME 20
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

        if(DEBUG) {
            dut->clock ^= 1;
            //if(dut->clock == 1){
            //    printf("Executing testebench,sim_time: %lu\n", sim_time);
                dut->a_0 = 1;
                dut->a_1 = 1;
                //dut->a_2 ^= 1;
                //dut->a_3 ^= 1;
            //}
        }
        else{
            printf("Executing testebench,sim_time: %lu\n", sim_time);
            dut->clock ^= 1;
            // state machine for testing the main behaviour
                if (dut->clock == 1)
                {
                    switch (state)
                    {
                    case 0:
                        dut->a_0 = 1;
                        dut->a_1 = 0;
                        //dut->a_2 = 0;
                        //dut->a_3 = 0;
                        state = 1;
                        break;
                    case 1:
                        dut->a_0 = 0;
                        dut->a_1 = 1;
                        //dut->a_2 = 0;
                        //dut->a_3 = 0;
                        state = 2;
                        break;
                    case 2:
                        dut->a_0 = 0;
                        dut->a_1 = 0;
                        //dut->a_2 = 1;
                        //dut->a_3 = 0;
                        state = 3;
                        break;
                    case 3:
                        dut->a_0 = 0;
                        dut->a_1 = 0;
                        //dut->a_2 = 0;
                        //dut->a_3 = 1;
                        state = 4;
                        break;
                    case 4:
                        dut->a_0 = 0;
                        dut->a_1 = 0;
                        //dut->a_2 = 0;
                        //dut->a_3 = 0; 
                        state = 0;
                        break;
                    default:
                        state = 0;
                        break;
                    }
                }
        }
            dut->eval();
            m_trace->dump(sim_time);
            sim_time++;

    }

    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}
