module AND(output out, input in_1, input in_2);
    wire nand_out; 

    nand(nand_out, in_1, in_2); 
    NOT not_gate(out, nand_out);
endmodule