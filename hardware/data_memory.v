module DataMemory(
    input clk, 
    input load, 
    input [14:0] adr, 
    input [15:0] d_in, 
    output [15:0] d_out,
    output [15:0] screen_out [8191:0],
    input [15:0] kb_in
    ); 

    reg [15:0] memory [24575:0]; 

    // set screen memory to initialise a half white and half black screen patern
    initial begin
       for (integer i=16383 ; i < 20479; i++) begin
            memory[i] = 65535;
       end
       memory[16383] = 16'b0101010101010101;
    end

    always @(posedge clk) begin
        if (load) begin
            memory[adr] <= d_in; 
        end 
    end

    // update keyboard memory map. 
    always begin
        memory[24575] = kb_in;
    end

    assign d_out = memory[adr]; 
    assign screen_out = memory[24574:16383];
endmodule