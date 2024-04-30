module ALU_tb; 
    reg [15:0] a16 = 16'b1011000010010101; 
    reg [15:0] b16 = 16'b0010011110010101; 

    reg zx, nx, zy, ny, f, no; 
    wire [15:0] alu_and_out, alu_adder_out; 
    wire zr, ng; 
    ALU alu(a16, b16, alu_and_out, alu_adder_out, 1'b1, 1'b0, 1'b1, 1'b0, f, no, zr, ng); 

    wire [15:0] and_out; 
    AND_16 and_16(a16, b16, and_out); 

    wire [15:0] adder_out; 
    wire adder_carry; 
    FULLADDER_16 fulladder_16(a16, b16, adder_carry, adder_out); 

    initial begin
        #10
        $display("------- STANDALONE : 16 BIT AND GATE -------"); 
        #10
        $display("A: %b, B: %b, OUTPUT: %b", a16, b16, and_out); 
        #10
        $display("------- ALU : 16 BIT ADDER -------"); 
        #10
        $display("A: %b, B: %b, sum out: %b, carry out: %b", a16, b16, alu_adder_out, adder_carry); 
        #10
        $display("------- ALU : 16 BIT AND GATE -------"); 
        #10
        $display("A: %b, B: %b, out: %b", a16, b16, alu_and_out); 
        $finish; 
    end
endmodule