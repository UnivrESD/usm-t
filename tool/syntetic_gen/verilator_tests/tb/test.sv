`include "tb/environment.sv"
program test(controller_intf intf);

    class my_trans extends transaction;
        function void pre_randomize();
            a_0.rand_mode(1);
            a_1.rand_mode(1);
            a_2.rand_mode(1);
            a_3.rand_mode(1);
            a_4.rand_mode(1);
        endfunction
    endclass

    //declaring environment instance
    environment env;
    my_trans my_tr;

    initial begin
        //creating environment
        env = new(intf);
        my_tr = new();

        //setting the repeat count of the generator
        env.gen.repeat_count = 1000;

        env.gen.trans = my_tr;

        //calling run of env, it issues calls to the generator and driver
        env.run();
    end
endprogram
