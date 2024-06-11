####### ONLY TESTED ON MAC OS. DEPENDENCY PATHS HAVE TO BE UPDATED WHEN USED ON LINUX ######
TARGET = computer

VERILOG_TOP = computer
VERILOG_SRC = $(VERILOG_TOP).v
CPP_SRC = main.cc

SDL_ROOT = /opt/homebrew/opt/sdl2
CFLAGS = `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

all: 
	verilator -I$(SDL_ROOT)/include/ -cc $(VERILOG_SRC) --exe $(CPP_SRC) -o $(TARGET) -CFLAGS "$(CFLAGS)" -LDFLAGS "$(LDFLAGS)"
	make -C ./obj_dir -f V$(TARGET).mk
	echo ------- TO EXECUTE THE COMPILED BINARY, RUN: ./obj_dir/$(TARGET) --------

clean:
	rm -r obj_dir 