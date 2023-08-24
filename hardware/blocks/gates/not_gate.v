module NOT(output out_val, input in_val);
	nand(out_val, in_val, 1); 
endmodule

module NOT_tb;
	reg in; 
	wire out;

	NOT not_gate(out, in); 

	initial begin
		// generate dumb file to view in gtkwave
    		$dumpfile("not_gate.vcd");
		$dumpvars(0, NOT_tb); 

		in = 1; 
		#10; // wait for 10 ns
		$display("NOT GATE : INPUT %d, OUTPUT=%d", in, out); 

		in = 0; 
		#10;
		$display("NOT GATE : INPUT %d, OUTPUT=%d\n", in, out); 

		$finish; 
	end
endmodule 

// Use NAND gate as the primitive gate to build the rest of the gates
// NOT
// AND
// OR
// XOR
