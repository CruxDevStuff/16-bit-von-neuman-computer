// 1 bit and 16 bit memory test benches. 

`timescale 1ns/100ps // define the minimum time unit used by the simulation

module ram_tb;
    reg _clk=0; 
    wire clk; 
    reg reset_n = 1; // set to 0 to send a reset (pull down like in real hardware)
    reg load = 1; 
    realtime capture = 0.0;

    always #5 _clk=~_clk; // invert clock every 5 ns
    assign clk = _clk; 

    reg data_in = 0; 
    wire data_out; 
    REGISTER register_1bit(clk, reset_n, load, data_in, data_out); 

    reg [15:0] data_in16 = {16{1'b0}}; 
    wire [15:0] data_out16; 
    REGISTER_16 register_16(clk, reset_n, load, data_in16, data_out16); 

    initial begin
        forever begin
            #2; 
            data_in = ~data_in; 
            data_in16 = ~data_in16; 
            // capture = $realtime;
            // $display("%t", capture); // uncomment to print the cycle count of the simulation in realtime.
        end
    end

    initial begin
        $display("REGISTER TESTBENCH"); 
        $dumpfile("register-dump.vcd");
        $dumpvars(3);
        #100000 // run simulation for 100000 timeunits (in this case 100000 ns as defined on top)
        $finish;
    end 

endmodule