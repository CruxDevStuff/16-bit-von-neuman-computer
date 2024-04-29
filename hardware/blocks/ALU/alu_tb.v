module ALU_tb; 
    reg [15:0] a16 = 16'b1111000010010101; 
    reg [15:0] b16 = 16'b0010011110010101; 

    reg a = 0, b = 0, c_in = 0; 
    wire sum, carry;  
    FULL_ADDER full_adder(a, b, c_in, sum, carry); 

    reg zx, nx, zy, ny, f, no; 
    wire [15:0] alu_out1, alu_out2; 
    wire zr, ng; 
    ALU alu(a16, b16, alu_out1, alu_out2, 1'b1, 1'b0, 1'b1, 1'b0, f, no, zr, ng); 

    wire [15:0] and_out; 
    AND_N #(.N(16)) and_16(a16, b16, and_out); 

    wire [15:0] adder_out; 
    ADDER_N #(.N(16)) adder_16(a16, b16, adder_out); 

    initial begin
        #10;
        $display("------- ALU TEST BENCH: 1 BIT FULL ADDER -------"); 
        // $display("AND: INPUT A %b, INPUT B %b, OUTPUT=%b", a16, b16, out); 
  
        $display("a: %b, b: %b, c: %b, sum: %b, carry: %b", a, b, c_in, sum, carry); 
        a = 0; b = 0; c_in = 1;
        #10
        $display("a: %b, b: %b, c: %b, sum: %b, carry: %b", a, b, c_in, sum, carry); 
        a = 0; b = 1; c_in = 0;
        #10
        $display("a: %b, b: %b, c: %b, sum: %b, carry: %b", a, b, c_in, sum, carry); 
        a = 0; b = 1; c_in = 1;
        #10
        $display("a: %b, b: %b, c: %b, sum: %b, carry: %b", a, b, c_in, sum, carry); 
        a = 1; b = 0; c_in = 0;
        #10
        $display("a: %b, b: %b, c: %b, sum: %b, carry: %b", a, b, c_in, sum, carry); 
        a = 1; b = 0; c_in = 1;
        #10
        $display("a: %b, b: %b, c: %b, sum: %b, carry: %b", a, b, c_in, sum, carry); 
        a = 1; b = 1; c_in = 0;
        #10
        $display("a: %b, b: %b, c: %b, sum: %b, carry: %b", a, b, c_in, sum, carry); 
        a = 1; b = 1; c_in = 1;
        #10
        $display("a: %b, b: %b, c: %b, sum: %b, carry: %b", a, b, c_in, sum, carry); 
        
        #10
        $display("------- ALU TEST BENCH: 16 BIT ADDER -------"); 
        #10
        $display("A: %b, B: %b, OUTPUT: %b", a16, b16, adder_out); 
        #10
        $display("------- ALU TEST BENCH: 16 BIT AND GATE -------"); 
        #10
        $display("A: %b, B: %b, OUTPUT: %b", a16, b16, and_out); 
        #10
        $display("------- ALU TEST BENCH: CONTROL BITS -------"); 
        #10 
        $display("x: %b, zx: %b, OUTPUT: %b", a16, 0, alu_out1); 
        #10
        $display("y: %b, zx: %b, OUTPUT: %b", b16, 0, alu_out2); 
        $finish; 
    end
endmodule