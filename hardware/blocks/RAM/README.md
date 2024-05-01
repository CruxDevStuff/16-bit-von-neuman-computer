# Compile and run testbench simulation and visualise the .vcd file on gtkwave
`iverilog -o ram.bin ram.v ram_tb.v && ./ram.bin`
`gtkwave ram-dump.vcd` <br> 

<img src="./vis-screenshot.png" width="1000" />

# Compile and Run on FPGA 
`make all` <br> 
`make prog` <br> 