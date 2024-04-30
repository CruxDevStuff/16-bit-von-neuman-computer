module ALU (input [15:0] x, y, output reg[15:0] out, out2, result, input zx, nx, zy, ny, f, no, output zr, ng);
    reg [15:0] x_in; 
    reg [15:0] y_in; 

    wire adder_carry; 
    wire [15:0] adder_out; 
    wire [15:0] and_out; 

    always @(x or y) begin
        if (zx) begin
            x_in = {16{1'b0}}; 
            // out = x_in; 
        end else begin
            x_in = x;  
            // out = x_in; 
        end

        if (nx) begin 
            x_in = ~x_in; 
            // out = x_in;
        end 

        if (zy == 1'b1) begin
            y_in = {16{1'b0}}; 
            // out2 = y_in; 
        end else begin
            y_in = y;  
            // out2 = y_in; 
        end

        if (ny) begin 
            y_in = ~y_in; 
            // out2 = y_in;
        end 
    end

    wire [15:0] tx = x_in; 
    wire [15:0] ty = y_in; 

    FULLADDER_16 adder16(tx, ty, adder_carry, adder_out); 
    AND_16 and16(tx, ty, and_out); 

    always @(adder_out or and_out) begin 

        out2 = adder_out; 
        out = and_out; 

        if (f) begin
            result = adder_out; 
        end else begin
            result = and_out; 
        end
    end

endmodule

module AND_16(input [15:0] x, y, output reg[15:0] out); 
    always @(x or y) begin
        {out} = x & y;  
    end
endmodule

module FULLADDER_16(input wire[15:0] x, y, output reg c_out, output reg[15:0] sum); 
    always @(x or y) begin
        {c_out, sum} = x + y; 
    end
endmodule
