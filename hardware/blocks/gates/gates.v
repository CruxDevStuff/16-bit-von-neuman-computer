module gates (
  input clk,
  input reset_n,
  input [0:4] io_button, 
  output [23:0] io_led
);

// AND gate 
assign io_led[0] = io_button[0] & io_button[1]; 
// NOT gate 
assign io_led[1] = ~io_button[1];
// OR gate 
assign io_led[2] = io_button[0] | io_button[1]; 
// NOR gate 
assign io_led[3] = ~(io_button[0] | io_button[1]); 

endmodule
