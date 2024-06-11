#include <iostream>
#include "SDL.h"
#include "SDL_timer.h"

#include <verilated.h>
#include "Vcomputer.h"
#include "include/main.h"

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

int main() {
    int ret; 

    ret = create_sdl_window(); 

    const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
    Vcomputer * computer_block = new  Vcomputer;

    poll_sdl_state();

	return 0; 
}