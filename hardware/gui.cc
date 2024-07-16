#include "gui.h"

void show_menu_bar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("Load ROM"); 
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void show_rom_table(uint16_t *contents, uint16_t pc_adr) {
    ImU32 current_row_color = ImGui::GetColorU32(ImVec4(255, 0, 0, 0.5f));

    ImGui::Begin("ROM", NULL, window_flags);

    if (ImGui::BeginTable("ROM table", 2, table_flags)) {
            // We could also set ImGuiTableFlags_SizingFixedFit on the table and all columns will default to ImGuiTableColumnFlags_WidthFixed.
            ImGui::TableSetupColumn("Address", column_flags, 30.0f);
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

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 work_pos = viewport->WorkPos; 
    ImVec2 work_size = viewport->WorkSize;
    ImGui::SetWindowPos(work_pos, true);
    ImGui::End();
}

void show_display(GLuint texture_id) {
    ImGui::Begin("Display");
    ImGui::Image((void*)(intptr_t)texture_id, ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 0));
    ImGui::End();
}