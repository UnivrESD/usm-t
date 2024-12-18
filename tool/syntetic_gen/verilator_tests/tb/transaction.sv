class transaction;
  //declaring the transaction items
  rand logic a_0,a_1,a_2,a_3,a_4;
    
  //post-randomize function, displaying randomized values of items 
  function void post_randomize();
    $display("--------- [Trans] post_randomize ------");
    $display("\t a_0 = %0h",a_0);
    $display("\t a_1 = %0h",a_1);
    $display("\t a_2 = %0h",a_2);
    $display("\t a_3 = %0h",a_3);
    $display("\t a_4 = %0h",a_4);
    $display("-----------------------------------------");
  endfunction
  
  //deep copy method
  function transaction do_copy();
    transaction trans;
    trans = new();
    trans.a_0 = this.a_0;
    trans.a_1 = this.a_1;
    trans.a_2 = this.a_2;
    trans.a_3 = this.a_3;
    trans.a_4 = this.a_4;
    return trans;
  endfunction
endclass
