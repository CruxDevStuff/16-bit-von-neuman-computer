module ALU_tb; 
    reg signed [15:0] a16 = 16'b0011000010010101; 
    reg signed [15:0] b16 = 16'b0010011110010101; 

    reg zx = 0; 
    reg nx = 1; 
    reg zy = 0; 
    reg ny = 1; 
    reg f = 0; 
    reg no = 1; 

    wire signed[15:0] alu_and_out, alu_adder_out, result; 
    wire zr, ng; 
    ALU alu(a16, b16, alu_and_out, alu_adder_out, result, zx, nx, zy, ny, f, no, zr, ng); 

    // wire [15:0] and_out; 
    // AND_16 and_16(a16, b16, and_out); 

    // wire signed[15:0] adder_out; 
    // wire adder_carry; 
    // FULLADDER_16 fulladder_16(a16, b16, adder_carry, adder_out); 

    initial begin
        // #10
        // $display("------- STANDALONE : 16 BIT AND GATE -------"); 
        // #10
        // $display("A: %b, B: %b, OUTPUT: %b", a16, b16, and_out); 
        // $dumpfile("alu.vcd");
        // $dumpvars(0, ALU_tb);
        #10
        $display("------- ALU : 16 BIT ADDER -------"); 
        #10
        $display("A: %d, B: %d, sum out: %d", a16, b16, alu_adder_out); 
        #10
        $display("------- ALU : 16 BIT AND GATE -------"); 
        #10
        $display("A: %b, B: %b, out: %b", a16, b16, alu_and_out); 
        #10
        $display("------- ALU : OUTPUT -------"); 
        #10
        $display("F: %b, OUTPUT: %b", f, result); 
        #10
        $display("------- ALU : ZERO AND NEG BITS -------"); 
        #10
        $display("ZR : %b, NG : %b", zr, ng); 
        $finish; 
    end
endmodule