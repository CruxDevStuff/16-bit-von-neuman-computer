// 32K rom for storing instructions
module ROM(
    input [14:0] adr_in,
    input load,
    output [15:0] d_out
);

    reg [15:0] memory [32767:0]; 

    parameter memory_file = "rect.hack"; // draws a rectangle of length RAM[0](set to 25 at the start of the program)
    // parameter memory_file = "add.hack"; // add's two numbers
    // parameter memory_file = "sub.hack"; // subtracts two numbers and stores it in two's complement form.
    
    initial begin
        $readmemb(memory_file, memory);
    end 

    assign d_out = memory[adr_in];
endmodule