module test(
clock,a_1_0,a_1_1,a_2_0,a_2_1,a_3_0,a_3_1,a_4_0,a_4_1,a_5_0,a_5_1,a_6_0,a_6_1,a_7_0,a_7_1,a_8_0,a_8_1,a_9_0,a_9_1,a_10_0,a_10_1,c_1_0,c_1_1,c_2_0,c_2_1,c_3_0,c_3_1,c_4_0,c_4_1,c_5_0,c_5_1,c_6_0,c_6_1,c_7_0,c_7_1,c_8_0,c_8_1,c_9_0,c_9_1,c_10_0,c_10_1);
input clock,a_1_0,a_1_1,a_2_0,a_2_1,a_3_0,a_3_1,a_4_0,a_4_1,a_5_0,a_5_1,a_6_0,a_6_1,a_7_0,a_7_1,a_8_0,a_8_1,a_9_0,a_9_1,a_10_0,a_10_1;
output c_1_0,c_1_1,c_2_0,c_2_1,c_3_0,c_3_1,c_4_0,c_4_1,c_5_0,c_5_1,c_6_0,c_6_1,c_7_0,c_7_1,c_8_0,c_8_1,c_9_0,c_9_1,c_10_0,c_10_1;
spec0 spec_sbm0(clock, a_1_0,a_1_1,c_1_0,c_1_1);
spec1 spec_sbm1(clock, a_2_0,a_2_1,c_2_0,c_2_1);
spec2 spec_sbm2(clock, a_3_0,a_3_1,c_3_0,c_3_1);
spec3 spec_sbm3(clock, a_4_0,a_4_1,c_4_0,c_4_1);
spec4 spec_sbm4(clock, a_5_0,a_5_1,c_5_0,c_5_1);
spec5 spec_sbm5(clock, a_6_0,a_6_1,c_6_0,c_6_1);
spec6 spec_sbm6(clock, a_7_0,a_7_1,c_7_0,c_7_1);
spec7 spec_sbm7(clock, a_8_0,a_8_1,c_8_0,c_8_1);
spec8 spec_sbm8(clock, a_9_0,a_9_1,c_9_0,c_9_1);
spec9 spec_sbm9(clock, a_10_0,a_10_1,c_10_0,c_10_1);
endmodule
