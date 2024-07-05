`timescale 1ns/100ps // define the minimum time unit used by the simulation

module ram_tb; 
    reg _clk=0; 
    wire clk; 

    always #5 _clk=~_clk; // invert clock every 5 ns
    assign clk = _clk; 

    integer rand_in;
    realtime capture = 0.0;
    reg reset_n = 1; // set value to 0 to reset(pull down like in real hardware)

    // ---------------------RAM 8 TEST ------------------------- // 
    reg [2:0] t_adr_8 = 3'b000; 
    reg [15:0] write_data_8 = {16{1'b1}}; 
    reg load_8 = 1'b1; 
    wire [15:0] ram_output_8; 

    // RAM8 ram8(clk, load_8, t_adr_8, write_data_8, ram_output_8);
    // ---------------------------------------------------------- // 


    // ----------------------RAM 64 TEST------------------------ // 
    // reg [5:0] t_adr_64 = 6'b111111; 
    // reg [15:0] write_data_64 = {16{1'b1}}; 
    // wire [15:0] ram_output_64; 
    // reg load_64 = 1'b1; 
    // RAM64 ram64(clk, load_64, t_adr_64, write_data_64, ram_output_64); 

    // // ----------------------RAM 512 TEST------------------------ // 
    // reg [8:0] t_adr_512 = 9'b001111111; 
    // reg [15:0] write_data_512 = {16{1'b0}}; 
    // wire [15:0] ram_output_512;
    // reg load_512 = 1'b1; 
    // RAM512 ram512(clk, load_512, t_adr_512, write_data_512, ram_output_512); 

    // // ----------------------RAM 4K TEST------------------------ // 
    // reg [11:0] t_adr_4k = 12'b111111000000; 
    // reg [15:0] write_data_4k = {16{1'b0}}; 
    // wire [15:0] ram_output_4k;
    // reg load_4k = 1'b1; 
    // RAM4K ram4k(clk, load_4k, t_adr_4k, write_data_4k, ram_output_4k); 
    // ----------------------RAM 4K TEST------------------------ // 
    reg [13:0] t_adr_16k = 14'b00000000000000; 
    reg [15:0] write_data_16k = {16{1'b0}}; 
    wire [15:0] ram_output_16k;
    reg load_16k = 1'b1; 
    RAM16K ram16k(clk, load_16k, t_adr_16k, write_data_16k, ram_output_16k); 

    initial begin
        $display("RAM TESTBENCH"); 
        $dumpfile("ram-dump.vcd");
        $dumpvars(2);

        $display("-------------- RAM 512 ---------------"); 
        rand_in = $random; 
        write_data_512 = rand_in[15:0]; 
        #10
        $display("ADDRESS: %b \n INPUT : %b \n OUTPUT: %b", t_adr_512, write_data_512, ram_output_512); 


        $display("-------------- RAM 4K ---------------"); 
        rand_in = $random; 
        write_data_4k = rand_in[15:0]; 
        #10
        $display("ADDRESS: %b \n INPUT : %b \n OUTPUT: %b", t_adr_4k, write_data_4k, ram_output_4k); 

        capture = $realtime;
        $display("%t", capture); // uncomment to print the cycle count of the simulation in realtime.

        $display("-------------- RAM 16K ---------------"); 
        rand_in = $random; 
        write_data_16k = rand_in[15:0]; 
        #10
        $display("ADDRESS: %b \n INPUT : %b \n OUTPUT: %b", t_adr_16k, write_data_16k, ram_output_16k); 


        $display("-----------------------------"); 
        // #100001; // run simulation for 100000 timeunits (in this case 100000 ns as defined on top)
        $display("VISUALISE THE SIMULATION ON GTKWAVE USING THE .vcd OUTPUT"); 
        $finish;
    end
endmodule