// 32K rom for storing instructions
module ROM(
    input [14:0] adr_in,
    input load,
    output [15:0] d_out
);

    reg [15:0] memory [32767:0]; 

    // parameter memory_file = "add.hack";
    parameter memory_file = "draw.hack";
    
    initial begin
        $readmemb(memory_file, memory);
    end 

    // uncomment to print contents of ROM at start of program
    // initial begin
    //     $display("START"); 
    //     for (integer i=0; i<32767; i++) begin
    //         $display("INS: %d: %b", i, memory[i]);
    //     end
    // end
    assign d_out = memory[adr_in];
endmodule