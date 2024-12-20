module test(
clock,a_1_0,a_1_1,a_2_0,a_2_1,c_1_0,c_2_0);
input clock,a_1_0,a_1_1,a_2_0,a_2_1;
output c_1_0,c_2_0;
spec0 spec_sbm0(a_1_0,a_1_1,c_1_0);
spec1 spec_sbm1(a_2_0,a_2_1,c_2_0);
endmodule
