module top (
  input clk,
  input reset_n,
  input [0:4] io_button, 
  output [23:0] io_led
);

assign io_led[0] = io_button[0]; 
assign io_led[1] = io_button[0]; 

endmodule
