#pragma once
#include "imgui.h"
#include "SDL_opengl.h"
#include <iostream>

#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH 512
#define ADDRESS_COLUMN_WIDTH 20
#define DATA_COLUMN_WIDTH 50

void show_menu_bar();
void show_rom_window(uint16_t *contents, uint16_t pc_adr);
void show_ram_window(uint16_t *contents, uint16_t cur_adr);
void show_display_window(GLuint texture_id);
void show_cpu_window();
static ImGuiTableFlags table_flags = ImGuiTableFlags_Borders | 
                                ImGuiTableFlags_NoSavedSettings;
                                // ImGuiTableFlags_RowBg;

static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoCollapse |
                                ImGuiWindowFlags_NoSavedSettings |
                                ImGuiWindowFlags_AlwaysAutoResize;

static ImGuiTableColumnFlags column_flags = ImGuiTableColumnFlags_WidthStretch | 
                                ImGuiTableColumnFlags_NoResize;
                                

