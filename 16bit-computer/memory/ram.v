module RAM8(
    input clk, load, 
    input [2:0] address, 
    input [15:0] data_in, 
    output wire [15:0] ram_out 
); 

    reg reset_n = 1; 

    reg [2:0] sel = 3'b001; 
    wire [15:0] reg_0_data, reg_1_data, reg_2_data, reg_3_data, 
    reg_4_data, reg_5_data, reg_6_data, reg_7_data; 
    wire load_0, load_1, load_2, load_3, load_4, load_5, load_6, load_7; 

    REGISTER_16 reg_0(clk, reset_n, load_0, 16'b0001, reg_0_data); 
    REGISTER_16 reg_1(clk, reset_n, load_1, 16'b0011, reg_1_data); 
    REGISTER_16 reg_2(clk, reset_n, load_2, 16'b0111, reg_2_data); 
    REGISTER_16 reg_3(clk, reset_n, load_3, 16'b1111, reg_3_data); 
    REGISTER_16 reg_4(clk, reset_n, load_4, 16'b0001, reg_4_data); 
    REGISTER_16 reg_5(clk, reset_n, load_5, 16'b0011, reg_5_data); 
    REGISTER_16 reg_6(clk, reset_n, load_6, 16'b0111, reg_6_data); 
    REGISTER_16 reg_7(clk, reset_n, load_7, 16'b1111, reg_7_data); 

    // read 
    mux_8to1 mux8(reg_0_data, reg_1_data, reg_2_data, reg_3_data, 
                    reg_4_data, reg_5_data, reg_6_data, reg_7_data, 
                    sel, ram_out); 

    // write
    demux_1to8 demux8(sel, load_0, load_1,
                    load_2, load_3, load_4,
                    load_5, load_6, load_7); 

endmodule