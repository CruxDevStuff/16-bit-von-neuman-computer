#include <iostream>
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_ttf.h"
#include <verilated.h>
#include "verilated_vcd_c.h"
#include "Vcomputer.h"
#include "Vcomputer___024root.h"
#include "include/main.h"

const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
Vcomputer * computer_block = new Vcomputer;
VerilatedVcdC *m_trace = new VerilatedVcdC;
int sim_time = 0; 

SDL_Window * window = NULL; 
SDL_Renderer * renderer = NULL; 
SDL_Texture * texture = NULL; 
SDL_Surface * surface = NULL; 

int pressed_key = 0; 

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


void tick_clock(Vcomputer *block) {
    computer_block->eval(); 
    update_dump();

    block->clk ^= 1;
    sim_time += 1;
}

PixelIndex pixel_coordinate_to_index(int x, int y) {
    int memory_byte_index = y * 32 + x / 16;
    int memory_bit_index = 15 - (x % 16); 

    int screen_byte_index = y * 128 + x / 8;
    int screen_bit_index = 7 - (x % 8); 

    PixelIndex pixel_index; 

    pixel_index.memory_byte_index = memory_byte_index; 
    pixel_index.memory_bit_index = memory_bit_index; 

    pixel_index.screen_byte_index = screen_byte_index;
    pixel_index.screen_bit_index = screen_bit_index;

    return pixel_index; 
}

void update_individual_pixel(int x, int y, bool state) {
    // TODO: check pixel coordinate range 
    Uint8* pixels = (Uint8*)surface->pixels;

    PixelIndex indexes = pixel_coordinate_to_index(x, y); 

    if (state == true) {
        pixels[indexes.screen_byte_index] |= (1 << indexes.screen_bit_index); 
    } else if (state == false) {
        pixels[indexes.screen_byte_index] &= ~(1 << indexes.screen_bit_index); 
    }
}

void map_memory_to_screen() {
    Uint8* pixels = (Uint8*)surface->pixels;

    for (int x = 0; x < 511; x++) {
        for (int y = 0; y < 255; y++) {
            PixelIndex indexes = pixel_coordinate_to_index(x, y); 
            pixels[indexes.screen_byte_index] = (Uint8)computer_block->screen_out[indexes.memory_byte_index];
        }
    }
}

/* returns state of a pixel. 
set "entire_word" to "true" to get the entire memory block(16 bits in decimal) 
that the pixel belongs to*/

int get_pixel(int x, int y, bool entire_word=false) {
    // // returns 0 - black, 1 - white, -1 - invalid
    Uint16* pixels = (Uint16*)surface->pixels;

    PixelIndex indexes = pixel_coordinate_to_index(x, y); 

    if (entire_word) {
        return (int)(std::bitset<16>(pixels[indexes.screen_byte_index])).to_ulong(); 
    } else {
        return (int)(std::bitset<1>(pixels[indexes.screen_byte_index])[indexes.screen_bit_index]);
    }
    
}

int poll_sim_state() {
    SDL_Event event_handler;
    bool quit = false;
    
    while(!quit) {
        tick_clock(computer_block); 
        map_memory_to_screen();

        computer_block->kb_in = pressed_key;

        // std::cout << sim_time << "\n";
        // std::cout << "CURRENT KEY : " << computer_block->rootp->computer__DOT__data_mem__DOT__memory[24575] << std::endl;
        // std::cout << computer_block->rootp-> << std::endl;

        // int state = get_pixel(9, 3, true);
        // std::cout << state << std::endl;

        // poll sdl
        SDL_StartTextInput();

		while(SDL_PollEvent(&event_handler) != 0) {
            pressed_key = 0;
            // do things according to user input type
            if(event_handler.type == SDL_QUIT) {
                quit = true;
            }

            if(event_handler.type == SDL_TEXTINPUT) {
                pressed_key = character_to_code_map[(char*)event_handler.text.text];
            }

            if (event_handler.type == SDL_KEYDOWN) {
                // TODO: not text keys like : enter, backspace handled here.
            }
        } 
    
        // std::cout << pressed_key; 
        std::cout << "---------" << std::endl;
        
        SDL_StopTextInput();
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