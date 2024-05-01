module top (
  input clk,
  input reset_n,
  output [23:0] io_led
);

  reg [47:0] counter;

  always @(posedge clk) begin
    if (!reset_n)
      counter <= 0;
    else
      counter <= counter + 1;
  end

  assign io_led = counter[47:24];
endmodule
