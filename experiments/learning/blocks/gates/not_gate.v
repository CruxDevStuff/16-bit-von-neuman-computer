module NOT(output out_val, input in_val);
	nand(out_val, in_val, 1); 
endmodule

module NOT8(out, in); 
	input [7:0]in; 
	output [7:0]out;

	genvar i;

	generate	
		for (i=0; i < 8; i=i+1) begin
			nand(out[i], in[i], 1); 
		end
	endgenerate
endmodule