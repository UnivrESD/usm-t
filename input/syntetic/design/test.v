module test(
clock,a_1,b_1,a_2,b_2,a_3,b_3,a_4,b_4,c_1,d_1,e_1,c_2,d_2,e_2,c_3,d_3,e_3,c_4,d_4,e_4);
input clock,a_1,b_1,a_2,b_2,a_3,b_3,a_4,b_4;
output c_1,d_1,e_1,c_2,d_2,e_2,c_3,d_3,e_3,c_4,d_4,e_4;
spec0 spec_sbm0(clock, a_1,b_1,c_1,d_1,e_1);
spec1 spec_sbm1(clock, a_2,b_2,c_2,d_2,e_2);
spec2 spec_sbm2(clock, a_3,b_3,c_3,d_3,e_3);
spec3 spec_sbm3(clock, a_4,b_4,c_4,d_4,e_4);
endmodule
