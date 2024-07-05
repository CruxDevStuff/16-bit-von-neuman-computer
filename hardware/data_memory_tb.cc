#include <iostream>
#include "SDL.h"
#include "SDL_timer.h"

#include <verilated.h>
#include "verilated_vcd_c.h"

// #include "Vcomputer.h"
#include "VDataMemory.h"

#include "include/main.h"

int sim_time = 0; 

int create_sdl_window() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Hack Computer",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT,
                                        0);

    if(!window) {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface) {
        std::cout << "Failed to get the surface from the window\n";
        return -1; 
    }

    SDL_UpdateWindowSurface(window);

    return 0;
}

int poll_sdl_state() {
    SDL_Event event_handler;
    bool quit = false;

    while(!quit) {
		while(SDL_PollEvent(&event_handler) != 0 ) {
            // do things according to user input type
            if(event_handler.type == SDL_QUIT) {
                quit = true;
            }
        }
	}
    return 0; 
}

int poll_sim_state() {
    poll_sdl_state(); 
}

int main() {
    // int ret; 

    // ret = create_sdl_window(); 
    std::cout << "Starting Testbench" << std::endl; 
    // const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};

    VDataMemory* data_memory_block = new VDataMemory;

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    data_memory_block->trace(m_trace, 5); 
    m_trace->open("data_memory_waveform.vcd");

    data_memory_block->clk = 0; 
    data_memory_block->load = 0; 
    data_memory_block->d_in = 0; 
    data_memory_block->eval(); 

    while (sim_time < MAX_SIM_TIME) {
        data_memory_block->clk ^= 1; 
        sim_time += 1; 
        
        if (sim_time == 1) {
            data_memory_block->adr = 0x1;
        }

        if (sim_time == 3) {
            data_memory_block->adr = 0x0;
            data_memory_block->d_in = 1; 
            data_memory_block->load = 1; 
        }

        if (sim_time == 4) {
            data_memory_block->load = 0; 
            data_memory_block->adr = 0x1;
        }

        if (sim_time == 5) {
            // data_memory_block->adr = 0x0;
            data_memory_block->adr = 16383;
            data_memory_block->d_in = 65535;
            data_memory_block->load = 1; 
        }

        if (sim_time == 6) {
            // data_memory_block->adr = 0x0;
            data_memory_block->adr = 0x0;
            data_memory_block->load = 0; 
        }

        if (sim_time == 7) {
            // data_memory_block->adr = 0x0;
            data_memory_block->adr = 16383;
            // data_memory_block->load = 0; 
        }


        data_memory_block->eval(); 
        m_trace->dump(sim_time); 
    } 

    std::cout << data_memory_block->screen_out[1];
    m_trace->close(); 
    delete data_memory_block; 
    exit(EXIT_SUCCESS);     
    // poll_sim_state();

	return 0; 
}