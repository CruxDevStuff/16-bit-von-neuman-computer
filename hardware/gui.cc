#include "gui.h"

ImVec2 rom_window_size;
ImVec2 ram_window_size;
ImVec2 cpu_window_size;
ImVec2 display_window_size;

void show_menu_bar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("Load ROM"); 
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void show_rom_window(uint16_t *contents, uint16_t pc_adr) {
    ImU32 current_row_color = ImGui::GetColorU32(ImVec4(255, 0, 0, 0.5f));

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowSize(ImVec2(0, viewport->WorkSize.y));

    ImGui::Begin("ROM", NULL, window_flags);

    if (ImGui::BeginTable("ROM table", 2, table_flags)) {
            // We could also set ImGuiTableFlags_SizingFixedFit on the table and all columns will default to ImGuiTableColumnFlags_WidthFixed.
            ImGui::TableSetupColumn("Address", column_flags, ADDRESS_COLUMN_WIDTH);
            ImGui::TableSetupColumn("Data", column_flags, 50.0f); // Default to 200.0f

            ImGui::TableHeadersRow();

            for (int row = 0; row < 32768; row++) {
                auto bit_string = std::bitset<16>(contents[row]).to_string().c_str();
                
                ImGui::TableNextRow();

                if (row == pc_adr) {
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, current_row_color);
                }

                for (int column = 0; column < 2; column++) {
                    ImGui::TableSetColumnIndex(column);
                    if (column == 0) {
                        ImGui::Text("%d", row);
                    } else if (column == 1) {
                        // ImGui::Text("%s", std::bitset<16>(contents[row]).to_string());
                        ImGui::Text("%s", bit_string);
                        // ImGui::Text("%s", current_data);
                    }
                }
            }
        ImGui::EndTable();
    }

    rom_window_size = ImGui::GetWindowSize();
    ImVec2 work_pos = viewport->WorkPos; 
    ImGui::SetWindowPos(work_pos, true);
    ImGui::End();
}

void show_display_window(GLuint texture_id) {
    ImGui::Begin("Display", NULL, window_flags);
    ImGui::Image((void*)(intptr_t)texture_id, ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 0));
    
    // anchor to right side of ROM window
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    display_window_size = ImGui::GetWindowSize();
    ImVec2 work_pos = viewport->WorkPos; 
    ImVec2 anchor_pos = ImVec2(work_pos.x + rom_window_size.x, work_pos.y);
    ImGui::SetWindowPos(anchor_pos, true);

    ImGui::End();
}

void show_ram_window(uint16_t *contents, uint16_t cur_adr) {
    ImU32 current_row_color = ImGui::GetColorU32(ImVec4(255, 0, 0, 0.5f));

    ImGui::SetNextWindowSize(ImVec2(rom_window_size.x, rom_window_size.y), 0);
    ImGui::Begin("RAM", NULL, window_flags);

    float row_height = ImGui::GetTextLineHeightWithSpacing();

    // first child window 
    ImVec2 child_size(0, 500); 
    ImGui::BeginChild("RAM", child_size);
    if (ImGui::BeginTable("general registers", 2, table_flags)) {
        ImGui::TableSetupColumn("Address", column_flags, ADDRESS_COLUMN_WIDTH);
        ImGui::TableSetupColumn("Data", column_flags, DATA_COLUMN_WIDTH);

        ImGui::TableHeadersRow();

        for (int row = 0; row <= 24574; row++) { // Increase rows to demonstrate scrolling
            ImGui::TableNextRow();
            auto bit_string = std::bitset<16>(contents[row]).to_string().c_str();

            for (int column = 0; column < 2; column++) {
                ImGui::TableSetColumnIndex(column);
                if (column == 0) {
                    ImGui::Text("%d", row);
                } else if (column == 1) {
                    ImGui::Text("%s", bit_string);
                }
            }
        }

        ImGui::EndTable();
    }
    ImGui::EndChild();

    ImGui::Separator(); 

    ImGui::Text("") ;
    ImGui::Text("KEYBOARD REGISTER");
    // show keyboard register table 
    ImGui::BeginChild("Keyboard Register", ImVec2(0,row_height*2.5));
    if (ImGui::BeginTable("register table", 2, table_flags)) {
        ImGui::TableSetupColumn("Address");
        ImGui::TableSetupColumn("Data");
        ImGui::TableHeadersRow();
        
        for (int row = 0; row < 1; row++) { 
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("24575");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", contents[24575]);
        }

        ImGui::EndTable();
    }
    ImGui::EndChild();

    // anchor window to right
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ram_window_size = ImGui::GetWindowSize();
    ImVec2 work_pos = viewport->WorkPos; 
    ImVec2 anchor_pos = ImVec2(viewport->WorkSize.x - ram_window_size.x, work_pos.y);
    ImGui::SetWindowPos(anchor_pos, true);

    ImGui::End();
}

void show_cpu_window() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    cpu_window_size = ImVec2(viewport->WorkSize.x - (rom_window_size.x + ram_window_size.x), viewport->WorkSize.y - display_window_size.y); 
    ImGui::SetNextWindowSize(cpu_window_size); 

    ImGui::Begin("CPU", NULL, window_flags);

    ImGui::SetWindowPos(ImVec2(viewport->WorkPos.x + rom_window_size.x, viewport->WorkPos.y + display_window_size.y));
    ImGui::End();
}