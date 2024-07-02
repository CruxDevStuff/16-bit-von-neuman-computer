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

SDL_Window * window = NULL; 
SDL_Renderer * renderer = NULL; 
SDL_Texture * texture = NULL; 
SDL_Surface * surface = NULL; 

int create_sdl_window() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    window = SDL_CreateWindow("Hack Computer",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
                            0);
    if (!window) {
        std::cout << "Failed to create window\n";
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED 
                                | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }

    surface = SDL_CreateRGBSurfaceWithFormat(SDL_SWSURFACE,
                                                SCREEN_WIDTH, 
                                                SCREEN_HEIGHT, 1, 
                                                SDL_PIXELFORMAT_INDEX1MSB); 
    if(!surface) {
        std::cout << "Failed to get the surface from the window\n";
        return -1; 
    }

    SDL_Color colors[2] = {{0, 0, 0, 255}, {255, 255, 255, 255}};
    SDL_SetPaletteColors(surface->format->palette, colors, 0, 2);

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

void update_pixel(int x, int y, bool state) {
    // TODO: check pixel coordinate range 

    Uint8* pixels = (Uint8*)surface->pixels;
    
    int byte_index = y * surface->pitch + x / 8;
    int bit_index = 7 - (x % 8); 
    
    if (state == true) {
        pixels[byte_index] |= (1 << bit_index); 
    } else if (state == false) {
        pixels[byte_index] &= ~(1 << bit_index); 
    }
}

int poll_sim_state() {
    SDL_Event event_handler;
    bool quit = false;

    while(!quit) {

        tick_clock(computer_block); 
        std::cout << sim_time << "\n";

        // std::cout << computer_block->screen_out[0] << std::endl; 

        
        update_dump(); 
        
        // poll sdl
		while(SDL_PollEvent(&event_handler) != 0) {
            // do things according to user input type
            if(event_handler.type == SDL_QUIT) {
                quit = true;
            }

        }

        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            if (y % 8 == 0) {
                for (int x = 0; x < SCREEN_WIDTH; x++) {
                    update_pixel(x, y, true); 
                }
            }
        }
        

        SDL_RenderClear(renderer);
        SDL_Texture * screen_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(screen_texture); 
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