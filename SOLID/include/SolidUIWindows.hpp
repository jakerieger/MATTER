#pragma once

#include <imgui/IconsFontAwesome6.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "SolidEditor.hpp"

namespace SolidUIWindows {
    inline static void EditorPreferences() {
        if (ImGui::BeginPopupModal("Editor Preferences")) {
            ImGui::Text("Editor Preferences");
            ImGui::Separator();
            ImGui::Text("General");

            ImGui::EndPopup();
        }
    }
}