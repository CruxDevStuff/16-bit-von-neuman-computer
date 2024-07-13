module CPU (
    input clk, 
    input reset, 
    input [15:0] instruction,
    input [15:0] mem_in, 
    output cpu_write, 
    output [15:0] cpu_data_out, 
    output [14:0] cpu_adr_out,
    output [14:0] pc_out
);
    PC pc(
        .clk(clk),
        .reset_n(reset),
        .load(0),
        .inc(1),
        .data_in(0),
        .pc_out(pc_out)
    );
endmodule

module computer(
        input clk, 
        output [15:0] screen_out [8191:0], 
        input [15:0] kb_in,
        input reset
);

    wire [15:0] mem_out = 0;
    wire load = 0;
    wire [14:0] mem_adr;

    wire [14:0] pc_out = 0;
    wire [15:0] cpu_data_out;
    wire [15:0] rom_out;

    // TODO: instantiate CPU
    CPU cpu( 
        .clk(clk),
        .reset(reset),
        .instruction(rom_out),
        .mem_in(mem_out),
        .cpu_write(load),
        .cpu_data_out(cpu_data_out),
        .cpu_adr_out(mem_adr),
        .pc_out(pc_out)
    );

    ROM rom(
        .adr_in(pc_out),
        .d_out(rom_out)
    );

    DataMemory data_mem(
        .clk(clk), 
        .load(load),
        .adr(mem_adr),
        .d_in(cpu_data_out),
        .d_out(mem_out),
        .screen_out(screen_out),
        .kb_in(kb_in)
    );

endmodule
