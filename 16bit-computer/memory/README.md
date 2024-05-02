# Compile and run testbench simulation and visualise the .vcd file on gtkwave
`iverilog -o register.bin register.v register_tb.v && ./register.bin`
`gtkwave register-dump.vcd` <br> 

<img src="./vis-screenshot.png" width="1000" />

# Compile and Run on FPGA 
`make all` <br> 
`make prog` <br> 