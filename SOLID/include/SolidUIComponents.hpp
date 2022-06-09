#pragma once

#include <imgui/IconsFontAwesome6.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

enum ProjectItemType {
    ProjectItemType_Folder,
    ProjectItemType_FolderEmpty,
    ProjectItemType_File,
    ProjectItemType_File_Script,
    ProjectItemType_File_Material,
    ProjectItemType_File_Texture,
    ProjectItemType_File_Model,
    ProjectItemType_File_Font,
    ProjectItemType_File_Sound,
    ProjectItemType_File_Scene
};

namespace SolidUIComponents {
    inline static bool ToggleButton(
        const char* label,
        const ImVec2 &size,
        bool &active,
        ImVec4 &selectedColor,
        ImVec4 &selectedHovered,
        ImVec4 &normalColor,
        ImVec4 &normalHovered
    ) {
        bool button_clicked = false;

        if (active) {
            ImGui::PushStyleColor(ImGuiCol_Button, selectedColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, selectedHovered);
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, normalHovered);
        }

        button_clicked |= ImGui::Button(label, size);

        ImGui::PopStyleColor(2);
        return button_clicked;
    }

    inline static bool ProjectItem(const char* label, ProjectItemType type, ImVec4 color) {
        bool clicked = false;
        switch (type) {
            case ProjectItemType_Folder:
                ImGui::TextColored(color, ICON_FA_FOLDER);
                break;
            case ProjectItemType_FolderEmpty:
                ImGui::TextColored(color, ICON_FA_FOLDER_OPEN);
                break;
            case ProjectItemType_File:
                ImGui::TextColored(color, ICON_FA_FILE);
                break;
            case ProjectItemType_File_Script:
                ImGui::TextColored(color, ICON_FA_FILE_CODE);
                break;
            case ProjectItemType_File_Material:
                ImGui::TextColored(color, ICON_FA_BRUSH);
                break;
            case ProjectItemType_File_Texture:
                ImGui::TextColored(color, ICON_FA_IMAGE);
                break;
            case ProjectItemType_File_Model:
                ImGui::TextColored(color, ICON_FA_SHAPES);
                break;
            case ProjectItemType_File_Font:
                ImGui::TextColored(color, ICON_FA_FONT);
                break;
            case ProjectItemType_File_Sound:
                ImGui::TextColored(color, ICON_FA_MUSIC);
                break;
            case ProjectItemType_File_Scene:
                ImGui::TextColored(color, ICON_FA_MAP);
                break;
            default:
                return false;
        }

        ImGui::SameLine();
        clicked |= ImGui::Selectable(label, false);

        return clicked;
    }

    inline static bool DragFloatN_Colored(
        const char* label, 
        float* v, 
        int components, 
        float v_speed, 
        float v_min, 
        float v_max, 
        const char* display_format,
        float power
    ) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        bool value_changed = false;
        ImGui::BeginGroup();
        ImGui::PushID(label);
        ImGui::PushMultiItemsWidths(components, ImGui::CalcItemWidth());

        for (int i = 0; i < components; i++) {
            static const ImU32 colors[] = {
                0xBB0000FF, // these are read backwards but the bits are still read left to right
                0xBB00FF00, // 00ff6a
                0xBBFF0000, // 0088ff
                0xBBFFFFFF, // white
            };

            ImGui::PushID(i);
            value_changed |= ImGui::DragFloat("##v", &v[i], v_speed, v_min, v_max, display_format, power);

            const ImVec2 min = ImGui::GetItemRectMin();
            const ImVec2 max = ImGui::GetItemRectMax();
            const float spacing = g.Style.FrameRounding;
            const float halfSpacing = spacing / 2;

            window->DrawList->AddLine({ min.x + spacing, max.y - halfSpacing }, { max.x - spacing, max.y - halfSpacing }, colors[i], 1);

            ImGui::SameLine(0, g.Style.ItemInnerSpacing.x);
            ImGui::PopID();
            ImGui::PopItemWidth();
        }

        ImGui::PopID();
        ImGui::TextUnformatted(label, ImGui::FindRenderedTextEnd(label));
        ImGui::EndGroup();

        return value_changed;
    }
}