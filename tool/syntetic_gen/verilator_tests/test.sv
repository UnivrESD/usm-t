/* Generated by Yosys 0.47+149 (git sha1 889894a6d, clang++ 18.1.8 -fPIC -O3) */

module test(clock, a_1, c_0, a_0);
  wire _00_;
  wire _01_;
  wire _02_;
  wire _03_;
  wire _04_;
  wire _05_;
  wire _06_;
  reg _07_ = 1'h0;
  input a_0;
  wire a_0;
  input a_1;
  wire a_1;
  output c_0;
  wire c_0;
  input clock;
  wire clock;
  assign _00_ = a_0 & _06_;
  assign _02_ = _05_ & _06_;
  assign _04_ = _01_ & _03_;
  assign _06_ = a_1 & _07_;
  always_ff @(posedge clock)
    _07_ <= a_0;
  assign _05_ = ~a_0;
  assign _01_ = ~_00_;
  assign _03_ = ~_02_;
  assign c_0 = ~_04_;
endmodule
