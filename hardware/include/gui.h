#pragma once
#include "imgui.h"
#include <iostream>

void show_menu_bar();
void show_rom_table(uint16_t *contents, uint16_t pc_adr);

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