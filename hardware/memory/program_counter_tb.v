`timescale 1ns/100ps // define the minimum time unit used by the simulation

module program_counter_tb; 
    reg _clk=0; 
    wire clk; 

    reg reset_n = 1; // set value to 0 to reset(pull down like in real hardware)
    reg inc = 1; 
    reg load = 0; 

    realtime capture = 0.0;

    always #5 _clk=~_clk; // invert clock every 5 ns
    assign clk = _clk; 

    reg [15:0] data_in16 = {16{1'b0}}; 
    wire [15:0] data_out16; 

    PROGRAM_COUNTER_16 pc_16(clk, reset_n, load, inc, data_in16, data_out16); 

    initial begin
        forever begin
            #2; 
            data_in16 = ~data_in16; 
            // capture = $realtime;
            // $display("%t", capture); // uncomment to print the cycle count of the simulation in realtime.
        end
    end

    initial begin
        $display("PROGRAM COUNTER TESTBENCH"); 
        $dumpfile("program_counter-dump.vcd");
        $dumpvars(3);
        #100000 // run simulation for 100000 timeunits (in this case 100000 ns as defined on top)
        $display("VISUALISE THE SIMULATION ON GTKWAVE USING THE .vcd OUTPUT"); 
        $finish;
    end 
endmodule