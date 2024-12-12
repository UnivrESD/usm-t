//gets the packet from generator and drive the transaction paket items into interface (interface is connected to DUT, so the items driven into interface signal will get driven in to DUT) 

class driver;

    //used to count the number of transactions
    int no_transactions;

    //creating virtual interface handle
    virtual counter_intf counter_vif;

    //creating mailbox handle
    mailbox gen2driv;

    //constructor
    function new(virtual counter_intf counter_vif,mailbox gen2driv);
        //getting the interface
        this.counter_vif = counter_vif;
        //getting the mailbox handles from  environment 
        this.gen2driv = gen2driv;
    endfunction

    //Reset task, Reset the Interface signals to default/initial values
    task reset;
        wait(counter_vif.rst);
        $display("--------- [DRIVER] Reset Started ---------");
        wait(!counter_vif.rst);
        $display("--------- [DRIVER] Reset Ended ---------");
    endtask

    //drives the transaction items to interface signals
    task drive;
        transaction trans;
        //get the transacation
        gen2driv.get(trans);
        //wait for the next negedge to inject the inputs into the DUT
        @(negedge counter_vif.clk);

        //inject the inputs
        counter_vif.in=trans.in;
        counter_vif.start=trans.start;
        counter_vif.dec=trans.dec;

        no_transactions++;
    endtask


    task main;
        wait(!counter_vif.rst);
        forever
            drive();
   endtask

endclass
