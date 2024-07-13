// 32K rom for storing instructions
module ROM(
    input [14:0] adr_in,
    output [15:0] d_out
);

    reg [15:0] memory [32767:0]; 

    initial begin
    // initialize rom from a file containing instructions
    $readmemb("add.hack", memory);
    end 

    initial begin
        $display("START"); 
        for (integer i=0; i<32767; i++) begin
            $display("INS: %d: %b", i, memory[i]);
        end
    end

endmodule