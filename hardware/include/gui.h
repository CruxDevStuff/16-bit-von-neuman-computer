#pragma once
#include "imgui.h"
#include "SDL_opengl.h"
#include <iostream>

#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH 512

void show_menu_bar();
void show_rom_table(uint16_t *contents, uint16_t pc_adr);
void show_display(GLuint texture_id);

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
                                

