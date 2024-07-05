// 16 bit program counter
module PROGRAM_COUNTER_16 (
    input clk, 
    input reset_n, 
    input load, 
    input inc, 
    input [15:0] data_in, 
    output [15:0] data_out
);
    reg [15:0] pc_value = 0;

    always @(posedge clk) begin
        if (!reset_n) begin
            pc_value <= {16{1'b0}}; 
        end else if (inc) begin
            pc_value <= pc_value + 1; 
        end else if(load) begin
            pc_value <= data_in; 
        end
    end
    assign data_out = pc_value; 
endmodule