#include "main.h"
#include "gui.h"

int get_random_flip(int const a = 255, int const b = 0) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 2);
  return (dis(gen) == 1)? a : b;
}

GLuint create_display_texture(int width, int height) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_id;
}

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

    window = SDL_CreateWindow("Hack Computer Hardware Simulator",
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

    texture_id = create_display_texture(SCREEN_WIDTH, SCREEN_HEIGHT);

    // setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;

    // set custom font
    ImFont* font = io->Fonts->AddFontFromFileTTF("include/Cousine-Regular.ttf", 22.0f);

    // set theme 
    ImGui::StyleColorsDark();

    // set window boder color
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0 / 255.0f, 143 / 255.0f, 17 / 255.0f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = style.Colors[ImGuiCol_TitleBg];

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

uint16_t* get_rom_contents() {
    tick_clock(computer_block); 
    static uint16_t rom_contents[32768];

    for (int i = 0; i <= 32768; i++) {
        rom_contents[i] = (int)std::bitset<16>(computer_block->rootp->computer__DOT__rom__DOT__memory[i]).to_ulong();
    }
    
    return rom_contents;
}

// get RAM contents 
uint16_t* get_ram_contents() {
    static uint16_t ram_contents[24576];

    for (int i = 0; i <= 24576; i++) {
        ram_contents[i] = (int)std::bitset<16>(computer_block->rootp->computer__DOT__data_mem__DOT__memory[i]).to_ulong();
    }
    
    return ram_contents;
}

void generate_random_texture() {
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            texture_data[y * SCREEN_WIDTH + x] = get_random_flip(); // Example pattern
        }
    }
}

void grayscale_to_rgb_data(uint8_t* rgb_out, const uint16_t* grayscale_in, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int grayscale_pixel = y * width + x;
            int grayscale_index = grayscale_pixel / 16;
            int bit_offset = 15 - (grayscale_pixel % 16);  // Start from most significant bit
            
            uint8_t pixel_value = (grayscale_in[grayscale_index] & (1 << bit_offset)) ? 255 : 0;
            
            // Flip both x and y coordinates
            int rgb_pixel = (height - 1 - y) * width + (width - 1 - x);
            int rgb_index = rgb_pixel * 3;
            rgb_out[rgb_index + 0] = pixel_value;  // R
            rgb_out[rgb_index + 1] = pixel_value;  // G
            rgb_out[rgb_index + 2] = pixel_value;  // B
        }
    }
}

void update_display_texture() {
    grayscale_to_rgb_data(rgb_data, computer_block->screen_out, SCREEN_WIDTH, SCREEN_HEIGHT);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, rgb_data);
}

int poll_sim_state() {
    // cache the rom_contents of the ROM once at start 
    uint16_t* rom_contents = get_rom_contents(); 

    uint16_t* ram_contents = get_ram_contents();

    unsigned char* rgb_data = new unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT * 3];

    while(!quit) {
        auto start_time = std::chrono::high_resolution_clock::now();
        
        if (run) {
            computer_block->reset = reset_computer;
            prev_pc = computer_block->rootp->computer__DOT__pc_out;
            tick_clock(computer_block); 
            computer_block->kb_in = pressed_key;
        }

        ram_contents = get_ram_contents();

        // std::cout << sim_time << "\n";
        // std::cout << "CURRENT KEY : " << computer_block->rootp->computer__DOT__data_mem__DOT__memory[24575] << std::endl;

        // poll sdl
        poll_sdl_events(); 

        update_display_texture();

        // start of a new Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // call all GUI stuff
        show_menu_bar(); 
        show_rom_window(rom_contents, computer_block->rootp->computer__DOT__pc_out);
        show_display_window(texture_id);
        show_ram_window(ram_contents, computer_block->rootp->computer__DOT__cpu__DOT__A_out);
        show_cpu_window(computer_block->rootp->computer__DOT__pc_out,
                        prev_pc, 
                        computer_block->rootp->computer__DOT__cpu__DOT__A_out, 
                        computer_block->rootp->computer__DOT__cpu__DOT__D_out,
                        run,
                        reset_computer,
                        computer_block->rootp->computer__DOT__cpu__DOT__alu_output
                        ); 
        
        std::cout << reset_computer << std::endl;           
        std::cout << computer_block->rootp->computer__DOT__pc_out << std::endl;
        std::cout << "---------" << std::endl;
        
        // render 
        ImGui::Render();
        glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
        glClearColor(background_color.x * background_color.w, background_color.y * background_color.w, background_color.z * background_color.w, background_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);

        // Calculate the loop rate (iterations per second)
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        double duration_seconds = duration.count();
        double loop_rate = 1/duration_seconds * 1e9;
        // std::cout << loop_rate << std::endl; // print loop rate in hz
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