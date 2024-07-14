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