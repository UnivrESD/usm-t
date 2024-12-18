//gets the packet from generator and drive the transaction paket items into interface (interface is connected to DUT, so the items driven into interface signal will get driven in to DUT) 
class driver;

    //used to count the number of transactions
    int no_transactions;

    //creating virtual interface handle
    virtual controller_intf controller_vif;

    //creating mailbox handle
    mailbox #(transaction) gen2driv;

    //constructor
    function new(virtual controller_intf controller_vif,mailbox #(transaction) gen2driv);
        //getting the interface
        this.controller_vif = controller_vif;
        //getting the mailbox handles from  environment 
        this.gen2driv = gen2driv;
    endfunction

    //drives the transaction items to interface signals
    task drive;
        transaction trans;
        //get the transacation
        gen2driv.get(trans);
        //wait for the next negedge to inject the inputs into the DUT
        @(negedge controller_vif.clk);

        //inject the inputs
        controller_vif.a_0=trans.a_0;
        controller_vif.a_1=trans.a_1;
        controller_vif.a_2=trans.a_2;
        controller_vif.a_3=trans.a_3;
        controller_vif.a_4=trans.a_4;

        no_transactions++;
    endtask

    task main;
        forever
            drive();
    endtask

endclass
