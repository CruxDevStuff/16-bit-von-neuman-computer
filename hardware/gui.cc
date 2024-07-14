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

void show_rom_table() {
    static ImGuiTableFlags table_flags = ImGuiTableFlags_Borders | 
                                    ImGuiTableFlags_NoSavedSettings;

    static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoSavedSettings |
                                    ImGuiWindowFlags_AlwaysAutoResize;

    static ImGuiTableColumnFlags column_flags = ImGuiTableColumnFlags_WidthStretch | 
                                    ImGuiTableColumnFlags_NoResize;

    ImGui::Begin("Data Memory", NULL, window_flags);

    if (ImGui::BeginTable("table1", 2, table_flags)) {
            // We could also set ImGuiTableFlags_SizingFixedFit on the table and all columns will default to ImGuiTableColumnFlags_WidthFixed.
            ImGui::TableSetupColumn("Address", column_flags, 30.0f);
            ImGui::TableSetupColumn("Data", column_flags, 50.0f); // Default to 200.0f

            ImGui::TableHeadersRow();

            for (int row = 0; row < 32768; row++) {
                ImGui::TableNextRow();
                for (int column = 0; column < 2; column++) {
                    ImGui::TableSetColumnIndex(column);
                    if (column == 0) {
                        ImGui::Text("%d", row);
                    } else if (column == 1) {
                        ImGui::Text("1010101010101010");
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