module NOT_tb;
	reg in; 
	wire out;

	reg [7:0] in_8; 
	wire [7:0] out_8; 

	NOT not_gate(out, in); 
	NOT8 not_gate_8(out_8, in_8); 

	initial begin
		// generate dumb file to view in gtkwave
    		$dumpfile("not_gate.vcd");
		$dumpvars(0, NOT_tb); 

		$display("-----------------------------\n1 BIT GATE\n-----------------------------"); 
		in = 1; 
		#10; // wait for 10 ns
		$display("NOT GATE : INPUT %d, OUTPUT=%d", in, out); 

		in = 0; 
		#10;
		$display("NOT GATE : INPUT %d, OUTPUT=%d\n", in, out); 

		$display("-----------------------------\n8 BIT GATE\n-----------------------------"); 

		in_8 = {8{1'b0}}; 
		#10
		$display("NOT GATE : INPUT %b, OUTPUT=%b", in_8, out_8); 

		in_8 = {8{1'b1}}; 
		#10
		$display("NOT GATE : INPUT %b, OUTPUT=%b", in_8, out_8); 


		in_8 = 01010110; 
		#10
		$display("NOT GATE : INPUT %b, OUTPUT=%b\n", in_8, out_8); 
		$finish; 
	end
endmodule 
