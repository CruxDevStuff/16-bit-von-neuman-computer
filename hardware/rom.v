// 32K rom for storing instructions
module ROM(
    input [14:0] adr_in,
    input load,
    output [15:0] d_out
);

    reg [15:0] memory [32767:0]; 

    parameter memory_file = "rect.hack";
    
    initial begin
        $readmemb(memory_file, memory);
    end 

    assign d_out = memory[adr_in];
endmodule