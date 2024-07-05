module computer(
        input clk, 
        output [15:0] screen_out [8191:0], 
        input [15:0] kb_in,
        input reset
    );

    wire [15:0] outM = 0;
    wire load = 0;
    wire [14:0] adr = 24575;
    
    DataMemory data_mem(
        .clk(clk), 
        .load(load),
        .adr(adr),
        .d_in(65535),
        .d_out(outM),
        .screen_out(screen_out),
        .kb_in(kb_in)
    );

endmodule
