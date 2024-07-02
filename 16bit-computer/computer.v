module computer(
        input clk, 
        output [15:0] out_m, 
        output [15:0] screen_out [8191:0], 
        input [15:0] kb_in,
        input reset
    );

    reg outM = 0;

    DataMemory data_mem(
        .clk(clk), 
        .load(0),
        .adr(15'b0),
        .d_in(16'b0),
        .d_out(out_m),
        .screen_out(screen_out),
        .kb_in(kb_in)
    );

    always @(posedge clk) begin

    end
    // assign out_m = outM; 
endmodule
