module OR_tb; 
    reg in_a, in_b; 
    wire out_; 

    OR or_gate(out_, in_a, in_b); 

    initial begin
        in_a <= 0; in_b <= 0;
        #10;
		$display("OR GATE : INPUT A=%d, INPUT B=%d OUTPUT=%d", in_a, in_b, out_); 

        in_a <= 0; in_b <= 1;
        #10;
		$display("OR GATE : INPUT A=%d, INPUT B=%d OUTPUT=%d", in_a, in_b, out_); 

        in_a <= 1; in_b <= 0;
        #10;         
		$display("OR GATE : INPUT A=%d, INPUT B=%d OUTPUT=%d", in_a, in_b, out_); 

        in_a <= 1; in_b <= 1;
        #10; 
		$display("OR GATE : INPUT A=%d, INPUT B=%d OUTPUT=%d\n", in_a, in_b, out_); 

        $finish; 
    end
endmodule