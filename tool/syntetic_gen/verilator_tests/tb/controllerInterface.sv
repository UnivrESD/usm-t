interface controller_intf(input clk);
  
  //declaring the signals
  logic  a_0,a_1,a_2,a_3,a_4;
  logic  c_0,c_1,c_2,c_3,c_4;
  
  modport dut (input clk,a_0,a_1,a_2,a_3,a_4, output c_0,c_1,c_2,c_3,c_4);
endinterface
