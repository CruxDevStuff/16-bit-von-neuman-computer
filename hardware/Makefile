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

#ROM 
ROM_VRLG_SRC = rom.v 

#PC 
PC_VRLG_SRC = program_counter.v

# SDL2
SDL_ROOT = /opt/homebrew/opt/sdl2
CFLAGS = `sdl2-config --cflags` -Iimgui
LDFLAGS = `sdl2-config --libs`
LDFLAGS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo 

# imgui
IMGUI_PATH = ../include/imgui
IMGUI_BACKENDS_PATH = $(IMGUI_PATH)/backends
IMGUI_FILES = $(IMGUI_PATH)/imgui_demo.cpp $(IMGUI_BACKENDS_PATH)/imgui_impl_sdl2.cpp $(IMGUI_BACKENDS_PATH)/imgui_impl_opengl3.cpp $(IMGUI_PATH)/imgui.cpp $(IMGUI_PATH)/imgui_draw.cpp $(IMGUI_PATH)/imgui_widgets.cpp $(IMGUI_PATH)/imgui_tables.cpp
IMGUI_INCLUDE = -I$(IMGUI_PATH) -I$(IMGUI_BACKENDS_PATH)

# Add imgui source files to CPP_SRC
CPP_SRC += $(IMGUI_FILES)

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LDFLAGS += $(LINUX_GL_LIBS) -ldl `sdl2-config --libs`
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LDFLAGS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo 
	LDFLAGS += -L/usr/local/lib -L/opt/local/lib
endif

V$(TOP_TARGET).mk: $(VERILOG_SRC)
	verilator --public -I$(SDL_ROOT)/include/ --trace -cc $(VERILOG_SRC) $(DMEM_VRLG_SRC) $(PC_VRLG_SRC) $(ROM_VRLG_SRC) --top $(VERILOG_TOP) --exe $(CPP_SRC) -o $(TOP_TARGET) -CFLAGS "$(CFLAGS) $(IMGUI_INCLUDE)" -LDFLAGS "$(LDFLAGS)"

all: V$(TOP_TARGET).mk
	make -C ./obj_dir -f V$(VERILOG_TOP).mk
	echo ------- TO EXECUTE THE COMPILED BINARY, RUN: ./obj_dir/$(TOP_TARGET) --------

dmem:
	verilator --public -I$(SDL_ROOT)/include/ --trace -cc $(DMEM_VRLG_SRC) --top $(DMEM_VRLG_TOP) --exe $(DMEM_CPP_SRC) --public -o $(DMEM_TARGET) -CFLAGS "$(CFLAGS) $(IMGUI_INCLUDE)" -LDFLAGS "$(LDFLAGS)"
	make -C ./obj_dir -f V$(DMEM_VRLG_TOP).mk
	echo ------- TO EXECUTE "DataMemory" RUN : ./obj_dir/$(DMEM_TARGET) --------

clean:
	rm -r obj_dir 
	rm imgui.ini
