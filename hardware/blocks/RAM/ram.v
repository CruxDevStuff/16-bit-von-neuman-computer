// 1 and 16 bit memory devices that resemble a D-Flip Flop. 

module REGISTER (
  input clk,
  input reset_n,
  input d_in, 
  output d_out
);

  reg bit_data; 

  always @(posedge clk) begin
    if (!reset_n) begin
      bit_data <= 0; 
    end else begin
      bit_data <= d_in; 
    end
  end
  
  assign d_out = bit_data; 
endmodule

module REGISTER_16(
  input clk,
  input reset_n,
  input [15:0] d_in, 
  output [15:0] d_out
);

  reg [15:0] bit_data; 

  always @(posedge clk) begin
    if (!reset_n) begin
      bit_data <= {16{1'b0}}; 
    end else begin
      bit_data <= d_in; 
    end
  end
  
  assign d_out = bit_data; 
endmodule