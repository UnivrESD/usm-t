  #include "Vtest.h"
  #include "verilated.h"
  int main(int argc, char** argv) {
      VerilatedContext* contextp = new VerilatedContext;
      contextp->commandArgs(argc, argv);
      Vtest* top = new Vtest{contextp};
      while (!contextp->gotFinish()) { top->eval(); }
      delete top;
      delete contextp;
      return 0;
  }
