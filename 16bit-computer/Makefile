####### ONLY TESTED ON MAC OS. DEPENDENCY PATHS HAVE TO BE UPDATED WHEN USED ON LINUX ######
TOP_TARGET = computer
VERILOG_TOP = computer
VERILOG_SRC = $(VERILOG_TOP).v
CPP_SRC = main.cc

# DataMemory 
DMEM_TARGET = dmem
DMEM_VRLG_TOP = DataMemory
DMEM_VRLG_SRC = data_memory.v
DMEM_CPP_SRC = data_memory_tb.cc

SDL_ROOT = /opt/homebrew/opt/sdl2
CFLAGS = `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`


V$(TOP_TARGET).mk: $(VERILOG_SRC)
	verilator -I$(SDL_ROOT)/include/ --trace -cc $(VERILOG_SRC) $(DMEM_VRLG_SRC) --top $(VERILOG_TOP) --exe $(CPP_SRC) -o $(TOP_TARGET) -CFLAGS "$(CFLAGS)" -LDFLAGS "$(LDFLAGS)"

all: V$(TOP_TARGET).mk
	make -C ./obj_dir -f V$(VERILOG_TOP).mk
	echo ------- TO EXECUTE THE COMPILED BINARY, RUN: ./obj_dir/$(TOP_TARGET) --------

dmem:
	verilator -I$(SDL_ROOT)/include/ --trace -cc $(DMEM_VRLG_SRC) --top $(DMEM_VRLG_TOP) --exe $(DMEM_CPP_SRC) -o $(DMEM_TARGET) -CFLAGS "$(CFLAGS)" -LDFLAGS "$(LDFLAGS)"
	make -C ./obj_dir -f V$(DMEM_VRLG_TOP).mk
	echo ------- TO EXECUTE "DataMemory" RUN : ./obj_dir/$(DMEM_TARGET) --------

clean:
	rm -r obj_dir 