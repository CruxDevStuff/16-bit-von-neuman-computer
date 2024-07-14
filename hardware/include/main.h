#include <string>
#include <iostream>
#include <unordered_map>
#include "gui.h"

#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <verilated.h>
#include "verilated_vcd_c.h"
#include "Vcomputer.h"
#include "Vcomputer___024root.h"

using namespace std;

#define SCREEN_HEIGHT 256*2
#define SCREEN_WIDTH 512*2
#define MAX_SIM_TIME 20 // clock edges to simulate

const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
Vcomputer * computer_block = new Vcomputer;
VerilatedVcdC *m_trace = new VerilatedVcdC;

SDL_Window * window = NULL; 
SDL_Renderer * renderer = NULL; 
SDL_Texture * texture = NULL; 
SDL_Surface * surface = NULL; 
SDL_Event event_handler;

char * glsl_version = NULL;
ImGuiIO * io = NULL;
SDL_GLContext gl_context = NULL;

ImVec4 background_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); // r, g, b, alpha

int pressed_key = 0; 
int sim_time = 0; 

bool quit = false;
bool show_demo_window = true;

struct PixelIndex {
    // index of pixel in the hack computer memory map 
    int memory_byte_index = -1; 
    int memory_bit_index = -1; 
    
    // index of pixel in the SDL surface array
    int screen_byte_index = -1; 
    int screen_bit_index = -1; 
}; 

unordered_map<string, int> character_to_code_map = {

    {"0", 48}, {"1", 49}, {"2", 50}, {"3", 51}, {"4", 52}, {"5", 53}, {"6", 54}, {"7", 55},
    {"8", 56}, {"9", 57},
    
    {"space", 32}, {"!", 33}, {"\"", 34}, {"#", 35}, {"$", 36}, {"%", 37}, {"&", 38}, 
    {"'", 39}, {"(", 40}, {")", 41}, {"*", 42}, {"+", 43}, {",", 44}, {"-", 45}, 
    {".", 46}, {"/", 47}, {":", 58}, {";", 59}, {"<", 60}, {"=", 61}, {">", 62}, 
    {"?", 63}, {"@", 64}, {"[", 91}, {"/", 92}, {"]", 93}, {"^", 94}, {"_", 95}, 
    {"`", 96}, {"{", 123}, {"|", 124}, {"}", 125}, {"~", 126},

    {"A", 65}, {"B", 66}, {"C", 67}, {"D", 68}, {"E", 69}, {"F", 70}, {"G", 71},
    {"H", 72}, {"I", 73}, {"J", 74}, {"K", 75}, {"L", 76}, {"M", 77}, {"N", 78}, {"O", 79},
    {"P", 80}, {"Q", 81}, {"R", 82}, {"S", 83}, {"T", 84}, {"U", 85}, {"V", 86}, {"W", 87},
    {"X", 88}, {"Y", 89}, {"Z", 90}, 
    
    {"a", 97}, {"b", 98}, {"c", 99}, {"d", 100}, {"e", 101}, {"f", 102}, {"g", 103},
    {"h", 104}, {"i", 105}, {"j", 106}, {"k", 107}, {"l", 108}, {"m", 109}, {"n", 110}, {"o", 111},
    {"p", 112}, {"q", 113}, {"r", 114}, {"s", 115}, {"t", 116}, {"u", 117}, {"v", 118}, {"w", 119},
    {"x", 120}, {"y", 121}, {"z", 122}, 

    // TODO: change keys to proper SDL key names.   
    {"DEL", 127}, {"newline", 128}, {"backSpace", 129}, {"leftArrow", 130}, {"upArrow", 131},
    {"rightArrow", 132}, {"downArrow", 133}, {"home", 134}, {"end", 135}, {"pageUp", 136},
    {"pageDown", 137}, {"insert", 138}, {"delete", 139}, {"esc", 140}, 
    
    {"F1", 141}, {"F2", 142}, {"F3", 143}, {"F4", 144}, {"F5", 145}, {"F6", 146}, {"F7", 147}, {"F8", 148}, {"F9", 149},
    {"F10", 150}, {"F11", 151}, {"F12", 152}
};
