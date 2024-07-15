#include "main.h"

int create_sdl_window() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    #if defined(__APPLE__)
        // GL 3.2 Core + GLSL 150
        glsl_version = "#version 150";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    #else
        // GL 3.0 + GLSL 130
        glsl_version = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    #endif
    
    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI| SDL_WINDOW_MAXIMIZED);

    window = SDL_CreateWindow("Hack Computer",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
                            window_flags);
    if (!window) {
        std::cout << "Failed to create window\n";
        return -1;
    }

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // enable vsync

    // setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;

    // set custom font
    ImFont* font = io->Fonts->AddFontFromFileTTF("include/Cousine-Regular.ttf", 22.0f);

    // set theme 
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4 title_bg = style.Colors[ImGuiCol_TitleBgActive];
    style.Colors[ImGuiCol_TitleBg] = title_bg;
    style.Colors[ImGuiCol_TitleBgCollapsed] = title_bg;

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

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

    int screen_byte_index = y * surface->pitch + x / 8;
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

void poll_sdl_events() {
    SDL_StartTextInput();

	while(SDL_PollEvent(&event_handler) != 0) {
        ImGui_ImplSDL2_ProcessEvent(&event_handler);

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

    SDL_StopTextInput();
}

// cache the contents of the ROM once at start 
uint16_t* get_rom_contents() {
    tick_clock(computer_block); 
    static uint16_t contents[32768];

    for (int i = 0; i < 32768; i++) {
        contents[i] = (int)std::bitset<16>(computer_block->rootp->computer__DOT__rom__DOT__memory[i]).to_ulong();
    }
    
    return contents;
}

int poll_sim_state() {
    uint16_t* contents = get_rom_contents();

    while(!quit) {
        tick_clock(computer_block); 

        computer_block->kb_in = pressed_key;

        // std::cout << sim_time << "\n";
        // std::cout << "CURRENT KEY : " << computer_block->rootp->computer__DOT__data_mem__DOT__memory[24575] << std::endl;

        // poll sdl
        poll_sdl_events(); 

        // start of a new Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // call all GUI stuff
        show_menu_bar(); 
        show_rom_table(contents);

        // std::cout << "---------" << std::endl;
        
        // render 
        ImGui::Render();
        glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
        glClearColor(background_color.x * background_color.w, background_color.y * background_color.w, background_color.z * background_color.w, background_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
	}
    
    end_dump(); 

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0; 
}

int main() {
    int ret; 

    start_dump(); 

    ret = create_sdl_window();

    poll_sim_state();

	return 0; 
}