module OR(input a, input b, output out);
    wire nand_out_a; 
    wire nand_out_b;
    wire nand_out_c; 
    wire and_out; 

    NOT not_gate_a(nand_out_a, a);
    NOT not_gate_b(nand_out_b, b);
    AND and_gate(and_out, nand_out_a, nand_out_b); 
    NOT not_gate_c(out, and_out); 
endmodule
