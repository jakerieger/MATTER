/** Copyright 2022 Jake Rieger
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <filesystem>
#include <imgui/IconsFontAwesome6.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "SolidUtils.hpp"

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

    inline static bool ProjectItem(std::filesystem::path path, ProjectItemType type, ImVec4 color) {
        bool clicked = false;
        std::string drop_target = "";
        const char* file_path = path.string().c_str();

        switch (type) {
            case ProjectItemType_Folder:
                ImGui::TextColored(color, ICON_FA_FOLDER);
                drop_target = "Folder";
                break;
            case ProjectItemType_FolderEmpty:
                ImGui::TextColored(color, ICON_FA_FOLDER_OPEN);
                drop_target = "Folder";
                break;
            case ProjectItemType_File:
                ImGui::TextColored(color, ICON_FA_FILE);
                drop_target = "File";
                break;
            case ProjectItemType_File_Script:
                ImGui::TextColored(color, ICON_FA_FILE_CODE);
                drop_target = "Script";
                break;
            case ProjectItemType_File_Material:
                ImGui::TextColored(color, ICON_FA_BRUSH);
                drop_target = "Material";
                break;
            case ProjectItemType_File_Texture:
                ImGui::TextColored(color, ICON_FA_IMAGE);
                drop_target = "Texture";
                break;
            case ProjectItemType_File_Model:
                ImGui::TextColored(color, ICON_FA_SHAPES);
                drop_target = "Model";
                break;
            case ProjectItemType_File_Font:
                ImGui::TextColored(color, ICON_FA_FONT);
                drop_target = "Font";
                break;
            case ProjectItemType_File_Sound:
                ImGui::TextColored(color, ICON_FA_MUSIC);
                drop_target = "Sound";
                break;
            case ProjectItemType_File_Scene:
                ImGui::TextColored(color, ICON_FA_MAP);
                drop_target = "Scene";
                break;
            default:
                return false;
        }

        ImGui::SameLine();
        clicked |= ImGui::Selectable(path.filename().string().c_str(), false);
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            ImGui::SetDragDropPayload(drop_target.c_str(), file_path, sizeof(char*) * (strlen(file_path) + 1));

            ImGui::EndDragDropSource();
        }

        return clicked;
    }

    inline static bool DragDropTarget(ProjectItemType type, ImVec2 &size) {
        bool dropped = false;

        ImGui::BeginChild("DragDropTarget", size, true);
        switch (type) {
            case ProjectItemType_Folder:
                ImGui::Text(ICON_FA_FOLDER);
                break;
            case ProjectItemType_FolderEmpty:
                ImGui::Text(ICON_FA_FOLDER_OPEN);
                break;
            case ProjectItemType_File:
                ImGui::Text(ICON_FA_FILE);
                break;
            case ProjectItemType_File_Script:
                ImGui::Text(ICON_FA_FILE_CODE);
                break;
            case ProjectItemType_File_Material:
                ImGui::Text(ICON_FA_BRUSH);
                break;
            case ProjectItemType_File_Texture:
                ImGui::Text(ICON_FA_IMAGE);
                break;
            case ProjectItemType_File_Model:
                ImGui::Text(ICON_FA_SHAPES);
                break;
            case ProjectItemType_File_Font:
                ImGui::Text(ICON_FA_FONT);
                break;
            case ProjectItemType_File_Sound:
                ImGui::Text(ICON_FA_MUSIC);
                break;
            case ProjectItemType_File_Scene:
                ImGui::Text(ICON_FA_MAP);
                break;
            default:
                return false;

        }

        ImGui::EndChild();

        dropped = ImGui::BeginDragDropTarget();
        return dropped;    
    }

    inline static bool DragFloatN_Colored(
        const char* label, 
        float* v, 
        int components, 
        float v_speed, 
        float v_min, 
        float v_max, 
        const char* display_format,
        float power,
        ImVec4 x_axis,
        ImVec4 y_axis,
        ImVec4 z_axis
    ) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        bool value_changed = false;
        ImGui::BeginGroup();
        ImGui::PushID(label);
        ImGui::PushMultiItemsWidths(components, ImGui::CalcItemWidth());

        unsigned int R = SolidUtils::ColorVecToIMU32(x_axis);
        unsigned int G = SolidUtils::ColorVecToIMU32(y_axis);
        unsigned int B = SolidUtils::ColorVecToIMU32(z_axis);

        for (int i = 0; i < components; i++) {
            static const ImU32 colors[] = {
                R, // these are read backwards but the bits are still read left to right
                G, // 00ff6a
                B, // 0088ff
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