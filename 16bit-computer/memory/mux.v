module mux_8to1(
    input[15:0] a, b, c, d, e, f, g, h,
    input [2:0] sel, 
    output reg [15:0] mux_out
); 

    always @(a or b or c or d or sel) begin
        case(sel)
            3'b000 : mux_out <= a; 
            3'b001 : mux_out <= b; 
            3'b010 : mux_out <= c; 
            3'b011 : mux_out <= d; 
            3'b100 : mux_out <= e; 
            3'b101 : mux_out <= f; 
            3'b110 : mux_out <= g; 
            3'b111 : mux_out <= h; 
        endcase
    end

endmodule

module demux_1to8 (
    input [2:0] sel, 
    output reg a, b, c, d, e, f, g, h
);
    always @(sel) begin
        case(sel)
            3'b000 : {a, b, c, d, e, f, g, h} <= {1'b1, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0}; 
            3'b001 : {a, b, c, d, e, f, g, h} <= {1'b0, 1'b1, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0};
            3'b010 : {a, b, c, d, e, f, g, h} <= {1'b0, 1'b0, 1'b1, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0};
            3'b011 : {a, b, c, d, e, f, g, h} <= {1'b0, 1'b0, 1'b0, 1'b1, 1'b0, 1'b0, 1'b0, 1'b0};
            3'b100 : {a, b, c, d, e, f, g, h} <= {1'b0, 1'b0, 1'b0, 1'b0, 1'b1, 1'b0, 1'b0, 1'b0};
            3'b101 : {a, b, c, d, e, f, g, h} <= {1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b1, 1'b0, 1'b0};
            3'b110 : {a, b, c, d, e, f, g, h} <= {1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b1, 1'b0};
            3'b111 : {a, b, c, d, e, f, g, h} <= {1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b1};
        endcase
    end
endmodule