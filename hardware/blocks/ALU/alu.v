module ALU (
    // operand input
    input [15:0] x, y,

    // output
    output [15:0] out, 
    
    // control bits
    input zx, nx, zy, ny, f, no, zr, ng
);

endmodule

module AND_N(input [15:0] x, y, output [15:0] out); 
    parameter N = 16; 
    genvar i; 

    generate
        for (i = 0; i < N; i= i+1) begin
            and(out[i], x[i], y[i]); 
        end
    endgenerate
endmodule

module FULL_ADDER(input a, b, c, output sum, carry);
    wire sum1, carry1; 
    wire sum2, carry2; 

    xor(sum1, a, b); 
    and(carry1, a, b); 

    xor(sum, sum1, c); 
    and(carry2, sum1, c); 

    or(carry, carry1, carry2); 
endmodule


module ADDER_N(input [15:0] x, y, output [15:0] out); 
    parameter N = 16; // define the adder bit length. can be externally overwridden to change the adder size.
    wire [N-1:0] carry_out, sum_out; 

    genvar i; 

    generate
        for (i = 0; i < N; i= i+1) begin
            if (i==0)
                FULL_ADDER full_adder(x[i], y[i], 1'b0, out[i], carry_out[i]); 
            else
                FULL_ADDER full_adder(x[i], y[i], carry_out[i-1], out[i], carry_out[i]); 
        end
    endgenerate

endmodule
