module XOR(output out, input a, input b);
    wire not_out_a; 
    wire not_out_b; 

    wire and_out_a; 
    wire and_out_b; 

    NOT not_gate_a(not_out_a, a);
    NOT not_gate_b(not_out_b, b); 

    AND and_gate_a(and_out_a, a, not_out_b); 
    AND and_gate_b(and_out_b, b, not_out_a);

    OR or_gate(out, and_out_a, and_out_b); 
endmodule