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
     
    always @(posedge clk) begin
        if (load) begin
            memory[adr] <= d_in; 
        end 
    end

    assign d_out = memory[adr]; 
    assign screen_out = memory[24574:16383];
    
endmodule