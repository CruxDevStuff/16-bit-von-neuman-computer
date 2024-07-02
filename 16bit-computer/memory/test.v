module ram_chip(
	input clk,
	
	input [15:0] BRAM_IN,// Data input to BRAM (Write)
	output reg [15:0] BRAM_OUT,// Data output from BRAM (Read)
	
	input [14:0] BRAM_ADDR_R,// Read address
	input [14:0] BRAM_ADDR_W,// Write address
	
	input B_CE_W,// Write Enable
	input B_CE_R);// Read enable

    parameter BRAM_size = 24576 - 1 ;
	
    reg [15:0] mem1 [BRAM_size:0];// This reg will be inferred as BRAM by Yosys. THis one uses 8096 Bytes (Entire BRAM space of LP1K).
    integer i;

    // initial begin
    //     for(i = 0; i < 24576; i++)// start with blank memory with 0 instead of x so that we can infer Yosys for BRAM.
	// 	    mem1[i] <= 16'd0;
    // end

    always@(posedge clk) begin
        if(B_CE_R) 
            BRAM_OUT <= mem1[BRAM_ADDR_R];	
		
	    if(B_CE_W) 
		    mem1[BRAM_ADDR_W] <= BRAM_IN;
    end	

endmodule

// module top (input clk); 
//     reg [7:0] data_in;
//     wire [7:0] data_out; 
//     reg [12:0] read_adr, write_adr; 
//     reg we, re; 
    
//     BRAM ram(clk, data_in, data_out, read_adr, write_adr, we, re);  
//     reg [7:0] out_reg; 

//     always @(posedge clk) begin
//         re <= 1; 
//         we <= 0;

//         out_reg <= data_out; 
//         read_adr <= {8{1'b0}};
//         write_adr <= {8{1'b1}};
//         data_in <= {8{1'b1}};
//     end
// endmodule