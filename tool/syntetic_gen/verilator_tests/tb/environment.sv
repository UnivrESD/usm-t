`include "tb/transaction.sv"
`include "tb/generator.sv"
`include "tb/driver.sv"

class environment;
  
  //generator and driver instance
  generator gen;
  driver    driv;
  
  //mailbox handle's
  mailbox #(transaction) gen2driv;
  
  //event for synchronization between generator and test
  event gen_ended;
  
  //virtual interface
  virtual controller_intf controller_vif;
  
  //constructor
  function new(virtual controller_intf controller_vif);
    //get the interface from test
    this.controller_vif = controller_vif;
    
    //creating the mailbox (Same handle will be shared across generator and driver)
    gen2driv = new();
    
    //creating generator and driver
    gen  = new(gen2driv,gen_ended);
    driv = new(controller_vif,gen2driv);
  endfunction
  
  task pre_test();
  endtask
  
  task test();
    fork 
        gen.main();
        driv.main();
    join_none
  endtask
  
  task post_test();
    wait(gen_ended.triggered);
    wait(gen.repeat_count == driv.no_transactions);
  endtask  
  
  //run task
  task run;
    pre_test();
    test();
    post_test();
    $finish;
  endtask
  
endclass

