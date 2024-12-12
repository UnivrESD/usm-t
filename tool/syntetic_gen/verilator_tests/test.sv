/* Generated by Yosys 0.47+149 (git sha1 889894a6d, clang++ 18.1.8 -fPIC -O3) */

module test(clock, a_2, a_3, a_4, a_0, c_1, c_2, c_3, c_4, c_0, a_1);
  wire _00_;
  wire _01_;
  wire _02_;
  wire _03_;
  wire _04_;
  wire _05_;
  wire _06_;
  wire _07_;
  wire _08_;
  wire _09_;
  wire _10_;
  wire _11_;
  wire _12_;
  wire _13_;
  wire _14_;
  wire _15_;
  wire _16_;
  wire _17_;
  reg _18_ = 1'h0;
  input a_0;
  wire a_0;
  input a_1;
  wire a_1;
  input a_2;
  wire a_2;
  input a_3;
  wire a_3;
  input a_4;
  wire a_4;
  output c_0;
  wire c_0;
  output c_1;
  wire c_1;
  output c_2;
  wire c_2;
  output c_3;
  wire c_3;
  output c_4;
  wire c_4;
  input clock;
  wire clock;
  assign _00_ = a_2 & a_3;
  assign _01_ = a_1 & _00_;
  assign _02_ = a_4 & _17_;
  assign _03_ = _01_ & _02_;
  assign _05_ = a_0 & _18_;
  assign _06_ = _15_ & _18_;
  assign _07_ = a_4 & _05_;
  assign _08_ = _01_ & _07_;
  assign _10_ = a_4 & _06_;
  assign _11_ = _01_ & _10_;
  assign _13_ = _09_ & _12_;
  assign _14_ = _04_ & _13_;
  assign _17_ = a_0 & _16_;
  always_ff @(posedge clock)
    _18_ <= a_0;
  assign _04_ = ~_03_;
  assign _09_ = ~_08_;
  assign _12_ = ~_11_;
  assign c_1 = ~_14_;
  assign _15_ = ~a_0;
  assign _16_ = ~_18_;
  assign c_4 = c_1;
  assign c_3 = c_1;
  assign c_2 = c_1;
  assign c_0 = a_0;
endmodule
