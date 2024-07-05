module RAM8(
    input clk, load, 
    input [2:0] address, 
    input [15:0] data_in, 
    output wire [15:0] ram_out 
); 

    reg reset_n = 1; // pull down - set to 0 to reset. 

    wire [15:0] reg_0_data, reg_1_data, reg_2_data, reg_3_data, 
    reg_4_data, reg_5_data, reg_6_data, reg_7_data; 
    wire load_0, load_1, load_2, load_3, load_4, load_5, load_6, load_7; 

    REGISTER_16 reg_0(clk, reset_n, load_0, data_in, reg_0_data); 
    REGISTER_16 reg_1(clk, reset_n, load_1, data_in, reg_1_data); 
    REGISTER_16 reg_2(clk, reset_n, load_2, data_in, reg_2_data); 
    REGISTER_16 reg_3(clk, reset_n, load_3, data_in, reg_3_data); 
    REGISTER_16 reg_4(clk, reset_n, load_4, data_in, reg_4_data); 
    REGISTER_16 reg_5(clk, reset_n, load_5, data_in, reg_5_data); 
    REGISTER_16 reg_6(clk, reset_n, load_6, data_in, reg_6_data); 
    REGISTER_16 reg_7(clk, reset_n, load_7, data_in, reg_7_data); 

    // read 
    mux_8to1 mux8(address, reg_0_data, reg_1_data, reg_2_data, reg_3_data, 
                    reg_4_data, reg_5_data, reg_6_data, reg_7_data, 
                    ram_out); 

    // write
    demux_1to8 demux8(load, address, load_0, load_1,
                    load_2, load_3, load_4,
                    load_5, load_6, load_7); 

endmodule

module RAM64(
    input clk, load, 
    input [5:0] address, 
    input [15:0] data_in, 
    output wire [15:0] ram_out 
); 

    wire [2:0] chip_adr = address[5:3]; 
    wire [2:0] reg_adr = address[2:0]; 

    wire [15:0] chip_out_0, chip_out_1, chip_out_2, 
                chip_out_3, chip_out_4, chip_out_5, chip_out_6, chip_out_7;

    wire load_0, load_1, load_2, load_3, load_4, 
                load_5, load_6, load_7; 

    RAM8 ram8_chip_0(clk, load_0, reg_adr, data_in, chip_out_0); 
    RAM8 ram8_chip_1(clk, load_1, reg_adr, data_in, chip_out_1); 
    RAM8 ram8_chip_2(clk, load_2, reg_adr, data_in, chip_out_2); 
    RAM8 ram8_chip_3(clk, load_3, reg_adr, data_in, chip_out_3); 
    RAM8 ram8_chip_4(clk, load_4, reg_adr, data_in, chip_out_4); 
    RAM8 ram8_chip_5(clk, load_5, reg_adr, data_in, chip_out_5); 
    RAM8 ram8_chip_6(clk, load_6, reg_adr, data_in, chip_out_6); 
    RAM8 ram8_chip_7(clk, load_7, reg_adr, data_in, chip_out_7); 

    // write 
    demux_1to8 demux8(load, chip_adr, load_0, load_1,
                    load_2, load_3, load_4,
                    load_5, load_6, load_7); 
    
    // read 
    mux_8to1 mux8(reg_adr, chip_out_0, chip_out_1, chip_out_2, 
                chip_out_3, chip_out_4, chip_out_5, chip_out_6, 
                chip_out_7, ram_out); 

endmodule


module RAM512(
    input clk, load, 
    input [8:0] address, 
    input [15:0] data_in, 
    output wire [15:0] ram_out 
); 

    wire [2:0] curr_chip_adr = address[8:6]; 
    wire [5:0] next_chip_adr = address[5:0]; 

    wire [15:0] chip_out_0, chip_out_1, chip_out_2, 
                chip_out_3, chip_out_4, chip_out_5, chip_out_6, chip_out_7;

    wire load_0, load_1, load_2, load_3, load_4, 
                load_5, load_6, load_7; 

    RAM64 ram64_chip_0(clk, load_0, next_chip_adr, data_in, chip_out_0); 
    RAM64 ram64_chip_1(clk, load_1, next_chip_adr, data_in, chip_out_1); 
    RAM64 ram64_chip_2(clk, load_2, next_chip_adr, data_in, chip_out_2); 
    RAM64 ram64_chip_3(clk, load_3, next_chip_adr, data_in, chip_out_3); 
    RAM64 ram64_chip_4(clk, load_4, next_chip_adr, data_in, chip_out_4); 
    RAM64 ram64_chip_5(clk, load_5, next_chip_adr, data_in, chip_out_5); 
    RAM64 ram64_chip_6(clk, load_6, next_chip_adr, data_in, chip_out_6); 
    RAM64 ram64_chip_7(clk, load_7, next_chip_adr, data_in, chip_out_7); 

    // write 
    demux_1to8 demux8(load, curr_chip_adr, load_0, load_1,
                    load_2, load_3, load_4,
                    load_5, load_6, load_7); 
    
    // // read 
    mux_8to1 mux8(curr_chip_adr, chip_out_0, chip_out_1, chip_out_2, 
                chip_out_3, chip_out_4, chip_out_5, chip_out_6, 
                chip_out_7, ram_out); 

endmodule

module RAM4K(
    input clk, load, 
    input [11:0] address, 
    input [15:0] data_in, 
    output wire [15:0] ram_out 
); 

    wire [2:0] curr_chip_adr = address[11:9]; 
    wire [8:0] next_chip_adr = address[8:0]; 

    wire [15:0] chip_out_0, chip_out_1, chip_out_2, 
                chip_out_3, chip_out_4, chip_out_5, chip_out_6, chip_out_7;

    wire load_0, load_1, load_2, load_3, load_4, 
                load_5, load_6, load_7; 


    RAM512 ram512_chip_0(clk, load_0, next_chip_adr, data_in, chip_out_0); 
    RAM512 ram512_chip_1(clk, load_1, next_chip_adr, data_in, chip_out_1); 
    RAM512 ram512_chip_2(clk, load_2, next_chip_adr, data_in, chip_out_2); 
    RAM512 ram512_chip_3(clk, load_3, next_chip_adr, data_in, chip_out_3); 
    RAM512 ram512_chip_4(clk, load_4, next_chip_adr, data_in, chip_out_4); 
    RAM512 ram512_chip_5(clk, load_5, next_chip_adr, data_in, chip_out_5); 
    RAM512 ram512_chip_6(clk, load_6, next_chip_adr, data_in, chip_out_6); 
    RAM512 ram512_chip_7(clk, load_7, next_chip_adr, data_in, chip_out_7); 

    // write 
    demux_1to8 demux8(load, curr_chip_adr, load_0, load_1,
                    load_2, load_3, load_4,
                    load_5, load_6, load_7); 
    
    // // read 
    mux_8to1 mux8(curr_chip_adr, chip_out_0, chip_out_1, chip_out_2, 
                chip_out_3, chip_out_4, chip_out_5, chip_out_6, 
                chip_out_7, ram_out); 
endmodule

module RAM16K(
    input clk, load, 
    input [13:0] address, 
    input [15:0] data_in, 
    output wire [15:0] ram_out 
); 

    wire [2:0] curr_chip_adr = address[13:11]; 
    wire [11:0] next_chip_adr = address[11:0]; 

    wire [15:0] chip_out_0, chip_out_1, chip_out_2, 
                chip_out_3, chip_out_4, chip_out_5, chip_out_6, chip_out_7;

    wire load_0, load_1, load_2, load_3, load_4, 
                load_5, load_6, load_7; 


    RAM4K ram4k_chip_0(clk, load_0, next_chip_adr, data_in, chip_out_0); 
    RAM4K ram4k_chip_1(clk, load_1, next_chip_adr, data_in, chip_out_1); 
    RAM4K ram4k_chip_2(clk, load_2, next_chip_adr, data_in, chip_out_2); 
    RAM4K ram4k_chip_3(clk, load_3, next_chip_adr, data_in, chip_out_3); 
    RAM4K ram4k_chip_4(clk, load_4, next_chip_adr, data_in, chip_out_4); 
    RAM4K ram4k_chip_5(clk, load_5, next_chip_adr, data_in, chip_out_5); 
    RAM4K ram4k_chip_6(clk, load_6, next_chip_adr, data_in, chip_out_6); 
    RAM4K ram4k_chip_7(clk, load_7, next_chip_adr, data_in, chip_out_7); 

    // write 
    demux_1to8 demux8(load, curr_chip_adr, load_0, load_1,
                    load_2, load_3, load_4,
                    load_5, load_6, load_7); 
    
    // // read 
    mux_8to1 mux8(curr_chip_adr, chip_out_0, chip_out_1, chip_out_2, 
                chip_out_3, chip_out_4, chip_out_5, chip_out_6, 
                chip_out_7, ram_out); 
endmodule

