// 16 bit program counter
module PC (
    input clk, 
    input reset_n, 
    input load, 
    input inc, 
    input [14:0] data_in, 
    output [14:0] pc_out 
);
    reg [14:0] pc_value = 0;

    always @(posedge clk) begin
        if (!reset_n) begin
            pc_value <= {15{1'b0}}; 
        end else if(load) begin
            pc_value <= data_in; 
        end else if (inc) begin
            pc_value <= pc_value + 1; 
        end
    end
    assign pc_out = pc_value; 
endmodule