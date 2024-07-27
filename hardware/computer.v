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

    assign cpu_data_out = alu_output;
    assign cpu_adr_out = A_out[14:0];
    assign cpu_write = (instruction[3] & instruction[15]);

    wire [15:0] A_out, D_out;
        
    // alu control bits
    wire zx_bit, nx_bit, zy_bit, ny_bit, f_bit, no_bit;
    wire a_or_m_bit;
    // alu status output bits
    wire zr_status, ng_status;
    wire [15:0] alu_output;

    // switch between data_memory value and A value
    wire [15:0] alu_input_mux_out;
    
    wire [15:0] a_input_mux_out;
    wire a_input_mux_bit;
    wire [15:0] a_inst_data;
    wire a_load_bit;

    wire d_load_bit;

    // PC load input 
    wire jgt_status, jeq_status, jge_status, jlt_status, jne_status, jle_status, jmp_status, null_status;
    wire pc_load;
    wire jump_bits_status, jump_condition;

    // Instruction Decode
    // check C or A instruction 
    assign a_input_mux_bit = instruction[15];
    assign a_load_bit = (instruction[5] | ~(instruction[15]));

    assign d_load_bit = (instruction[15] & instruction[4]);

    assign a_inst_data = {1'b0, instruction[14:0]};

    assign a_or_m_bit = instruction[12];

    // decode alu control signals
    assign zx_bit = instruction[11];
    assign nx_bit = instruction[10];
    assign zy_bit = instruction[9];
    assign ny_bit = instruction[8];
    assign f_bit = instruction[7];
    assign no_bit = instruction[6];
    
    // PC load wires
    // JUMP 
    assign jgt_status = ~(zr_status | ng_status);
    assign jeq_status = zr_status;
    assign jge_status = ~(ng_status);
    assign jlt_status = ng_status;
    assign jne_status = ~(zr_status);
    assign jle_status = (zr_status | ng_status);
    assign jmp_status = 1;
    assign null_status = 0;

    mux1_8to1 pc_load_mux(
        .sel(instruction[2:0]),
        .a(null_status),
        .b(jgt_status),
        .c(jeq_status),
        .d(jge_status),
        .e(jlt_status),
        .f(jne_status),
        .g(jle_status),
        .h(jmp_status),
        .mux_out(pc_load)
    );

    PC pc(
        .clk(clk),
        .reset_n(reset),
        .load((pc_load & instruction[15])),
        .inc(1),
        .data_in(A_out[14:0]),
        .pc_out(pc_out)
    );

    mux16_2to1 a_input_mux(
        .sel(a_input_mux_bit),
        .a(a_inst_data),
        .b(alu_output),
        .mux_out(a_input_mux_out)
    );


    REGISTER_16 A(
        .clk(clk),
        .reset_n(reset),
        .load(a_load_bit),
        .d_in(a_input_mux_out), 
        .d_out(A_out)
    );

    REGISTER_16 D(
        .clk(clk),
        .reset_n(reset),
        .load(d_load_bit),
        .d_in(alu_output), 
        .d_out(D_out)
    );

    mux16_2to1 alu_input_mux(
        .sel(a_or_m_bit),
        .a(A_out),
        .b(mem_in),
        .mux_out(alu_input_mux_out)
    );

    ALU alu(
        .x(D_out),
        .y(alu_input_mux_out),
        .result(alu_output),
        .zx(zx_bit),
        .nx(nx_bit),
        .zy(zy_bit),
        .ny(ny_bit),
        .f(f_bit),
        .no(no_bit),
        .zr(zr_status),
        .ng(ng_status)
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
        .d_out(rom_out),
        .load(1)
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
