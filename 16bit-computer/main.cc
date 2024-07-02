#include <iostream>
#include "SDL.h"
#include "SDL_timer.h"

#include <verilated.h>
#include "verilated_vcd_c.h"
#include "Vcomputer.h"
#include "include/main.h"

const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
Vcomputer * computer_block = new Vcomputer;
VerilatedVcdC *m_trace = new VerilatedVcdC;
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

void tick_clock(Vcomputer *block) {
    computer_block->eval();            
    block->clk ^= 1;
    sim_time += 1;
}

void end_dump() {
    m_trace->close(); 
    delete computer_block; 
    exit(EXIT_SUCCESS);  
}

void start_dump() {
    Verilated::traceEverOn(true);
    computer_block->trace(m_trace, 5); 
    m_trace->open("computer_waveform.vcd");
}

void update_dump() {
    m_trace->dump(sim_time); 
}

int poll_sim_state() {
    SDL_Event event_handler;
    bool quit = false;

    while(!quit) {

        tick_clock(computer_block); 
        // std::cout << sim_time << "\n";

        std::cout << computer_block->screen_out[0] << std::endl; 

        
        update_dump(); 
        
        // poll sdl
		while(SDL_PollEvent(&event_handler) != 0) {
            // do things according to user input type
            if(event_handler.type == SDL_QUIT) {
                quit = true;
            }

        }
	}
    
    end_dump(); 

    return 0; 
}

int main() {
    int ret; 

    start_dump(); 

    ret = create_sdl_window();

    poll_sim_state();

	return 0; 
}