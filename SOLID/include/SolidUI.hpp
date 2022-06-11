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

#include <stdio.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <map>

#include <glad/glad.h>
#include <imgui/IconsFontAwesome6.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <pugixml.hpp>
#include <Str.h>

#include "SolidUtils.hpp"
#include "SolidLogger.hpp"
#include "SolidProfiler.hpp"
#include "SolidUIComponents.hpp"
#include "SolidProject.hpp"
#include "SolidScene.hpp"
#include "SolidGameObject.hpp"
#include "SolidModel.hpp"
#include "SolidMeshRenderer.hpp"
#include "SolidMaterial.hpp"
#include "SolidUIWindows.hpp"
#include "Windows/Dialogs.hpp"
// #include <WIN32/Dialogs.hpp>

/**
 * @brief All SOLID UI related code belongs to the SolidUI namespace.
 * 
 * @attention All SolidUI code is experimental and subject to change.
 * @note SolidUI is a namespace and should not be used as a class.
 * @author Jake Rieger
 */
namespace SolidUI {
    // Intialize our theme colors dictionary
    static std::map<std::string, ImVec4> colors {
        { "panel",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "scene",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "frame",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "accent",        ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "border",        ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "text",          ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "text_inactive", ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "selected",      ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "header",        ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "menu",          ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "success",       ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "warning",       ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "error",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
    };

    // Initialize our window style vars
    static float window_rounding = 0.0f;
    static float frame_rounding = 0.0f;
    static float border_size = 1.0f;

    static char console_search_buffer[256];

    // Toolbar button states
    //                                       move   rotate  scale
    static bool transformation_states[3] = { true, false, false };
    //                             snap   enabled
    static bool grid_states[2] = { true, true };
    //                               wireframe solid  lit
    static bool render_states[3] = { false,    true, false };

    static unsigned int game_object_selected_id = 0;

    static char* textureName = "None";

    inline static std::map<std::string, ImVec4> GetColors() { return colors; }

    struct ProjectAssets {
        std::vector<std::filesystem::path> textures;
        std::vector<std::filesystem::path> meshes;
        std::vector<std::filesystem::path> materials;
        std::vector<std::filesystem::path> scenes;
        std::vector<std::filesystem::path> game_objects;
        std::vector<std::filesystem::path> scripts;
        std::vector<std::filesystem::path> audio;
        std::vector<std::filesystem::path> fonts;
    };

    static ProjectAssets project_assets;

    namespace State {
        namespace EditorPreferences {
            static bool show_preferences = false;
            static bool selected_general = true;
            static bool selected_appearance = false;
            static bool selected_external_tools = false;
        }

        namespace Console {
            LogEntry *log_entry = nullptr;
            static bool console_paused = false;
        }
        
        static bool show_build_settings = false;
    }

    namespace Helpers {
        inline static void LoadColors(std::string themeName) {
            std::string defaultTheme = SolidUtils::GetEditorThemesPath() + "\\" + themeName + ".xml";
            pugi::xml_document themeDoc;
            pugi::xml_parse_result result = themeDoc.load_file(defaultTheme.c_str());

            if (!result)
                std::cout << "Failed to load theme file: " << defaultTheme << std::endl;

            for (pugi::xml_node color: themeDoc.child("theme").child("colors").children("color")) {
                std::string name = color.attribute("name").value();
                std::string hex = color.attribute("value").value();
                float alpha = color.attribute("opacity").as_float();

                ImVec4 colorVec = SolidUtils::ColorVecFromHex(hex.c_str(), alpha);
                colors[name] = colorVec;
            }

            pugi::xml_node window = themeDoc.child("theme").child("window");
            window_rounding = window.attribute("window_rounding").as_float();
            frame_rounding = window.attribute("frame_rounding").as_float();
            border_size = window.attribute("border_width").as_float();
        }

        inline static void ApplyColors() {
            ImGuiStyle* style = &ImGui::GetStyle();
            ImVec4* styleColors = style->Colors;

            style->WindowRounding = window_rounding;
            style->FrameRounding = frame_rounding;
            style->WindowBorderSize = border_size;
            style->FrameBorderSize = border_size;
            style->TabRounding = frame_rounding;

            styleColors[ImGuiCol_Text]                   = colors["text"];
            styleColors[ImGuiCol_TextDisabled]           = colors["text_inactive"];
            styleColors[ImGuiCol_WindowBg]               = colors["panel"];
            styleColors[ImGuiCol_ChildBg]                = colors["frame"];
            styleColors[ImGuiCol_PopupBg]                = colors["menu"];
            styleColors[ImGuiCol_Border]                 = colors["border"];
            styleColors[ImGuiCol_BorderShadow]           = ImVec4(0.f, 0.f, 0.f, 0.f);
            styleColors[ImGuiCol_FrameBg]                = colors["frame"];
            styleColors[ImGuiCol_FrameBgHovered]         = colors["frame"];
            styleColors[ImGuiCol_FrameBgActive]          = colors["frame"];
            styleColors[ImGuiCol_TitleBg]                = colors["panel"];
            styleColors[ImGuiCol_TitleBgActive]          = colors["panel"];
            styleColors[ImGuiCol_TitleBgCollapsed]       = colors["panel"];
            styleColors[ImGuiCol_MenuBarBg]              = colors["menu"];
            styleColors[ImGuiCol_ScrollbarBg]            = colors["panel"];
            styleColors[ImGuiCol_ScrollbarGrab]          = colors["selected"];
            styleColors[ImGuiCol_ScrollbarGrabHovered]   = colors["selected"];
            styleColors[ImGuiCol_ScrollbarGrabActive]    = colors["selected"];
            styleColors[ImGuiCol_CheckMark]              = colors["text"];
            styleColors[ImGuiCol_SliderGrab]             = colors["accent"];
            styleColors[ImGuiCol_SliderGrabActive]       = colors["accent"];
            styleColors[ImGuiCol_Button]                 = colors["selected"];
            styleColors[ImGuiCol_ButtonHovered]          = SolidUtils::ChangeColorAlpha(colors["selected"], 0.7f);
            styleColors[ImGuiCol_ButtonActive]           = SolidUtils::ChangeColorAlpha(colors["selected"], 0.55f);
            styleColors[ImGuiCol_Header]                 = colors["header"];
            styleColors[ImGuiCol_HeaderHovered]          = colors["accent"];
            styleColors[ImGuiCol_HeaderActive]           = colors["accent"];
            styleColors[ImGuiCol_Separator]              = SolidUtils::ChangeColorAlpha(styleColors[ImGuiCol_Border], 0.67f);
            styleColors[ImGuiCol_SeparatorHovered]       = colors["accent"];
            styleColors[ImGuiCol_SeparatorActive]        = colors["accent"];
            styleColors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
            styleColors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
            styleColors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
            styleColors[ImGuiCol_Tab]                    = colors["header"];
            styleColors[ImGuiCol_TabHovered]             = colors["selected"];
            styleColors[ImGuiCol_TabActive]              = colors["selected"];
            styleColors[ImGuiCol_TabUnfocused]           = styleColors[ImGuiCol_Tab];
            styleColors[ImGuiCol_TabUnfocusedActive]     = styleColors[ImGuiCol_TabActive];
            styleColors[ImGuiCol_TableBorderLight]       = ImVec4(0.f, 0.f, 0.f, 0.f);
            styleColors[ImGuiCol_TableBorderStrong]      = ImVec4(0.f, 0.f, 0.f, 0.f);
            styleColors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            styleColors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            styleColors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            styleColors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            styleColors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
            styleColors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
            styleColors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
            styleColors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            styleColors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
            styleColors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
            styleColors[ImGuiCol_DragDropTarget]         = colors["accent"];
            styleColors[ImGuiCol_NavHighlight]           = ImVec4(30.f / 255.f, 30.f / 255.f, 30.f / 255.f, 1.00f);
            styleColors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            styleColors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            styleColors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
        }

        inline static void LoadFonts(ImGuiIO& io) {
            io.Fonts->AddFontFromFileTTF((SolidUtils::GetEditorFontsPath() + "/TitilliumWeb-Regular.ttf").c_str(), 20.0f);

            ImFontConfig config;
            config.MergeMode = true;
            config.GlyphMinAdvanceX = 12.0f;
            static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
            io.Fonts->AddFontFromFileTTF((SolidUtils::GetEditorFontsPath() + "/fa-regular-400.ttf").c_str(), 12.0f, &config, icon_ranges);
            io.Fonts->AddFontFromFileTTF((SolidUtils::GetEditorFontsPath() + "/fa-solid-900.ttf").c_str(), 12.0f, &config, icon_ranges);

            // Fonts[1]
            ImFont* interfaceBold = io.Fonts->AddFontFromFileTTF((SolidUtils::GetEditorFontsPath() + "/TitilliumWeb-SemiBold.ttf").c_str(), 20.0f);

            // Fonts[2]
            ImFont* iconsLarge = io.Fonts->AddFontFromFileTTF((SolidUtils::GetEditorFontsPath() + "/fa-regular-400.ttf").c_str(), 36.0f, &config, icon_ranges);

            // Fonts[3]
            ImFont* consoleFont = io.Fonts->AddFontFromFileTTF((SolidUtils::GetEditorFontsPath() + "/FiraCode-Medium.ttf").c_str(), 16.0f);

            // Fonts[4]
            ImFont* consoleFontBold = io.Fonts->AddFontFromFileTTF((SolidUtils::GetEditorFontsPath() + "/FiraCode-Bold.ttf").c_str(), 16.0f);
        }
    
        inline static void ParseProjectAssets(SolidProject &project) {
            project_assets.textures.clear();
            project_assets.meshes.clear();
            project_assets.materials.clear();
            project_assets.fonts.clear();
            project_assets.scripts.clear();
            project_assets.scenes.clear();
            project_assets.game_objects.clear();
            project_assets.audio.clear();
            project_assets.fonts.clear();

            for (const auto &entry : std::filesystem::directory_iterator(project.GetProjectPath())) {
                SolidUtils::FileType type = SolidUtils::GetFileType(entry.path().extension().string());

                switch (type) {
                    case SolidUtils::FileType::FileType_Font:
                        project_assets.fonts.push_back(entry.path());
                        break;
                    case SolidUtils::FileType::FileType_Script:
                        project_assets.scripts.push_back(entry.path());
                        break;
                    case SolidUtils::FileType::FileType_Scene:
                        project_assets.scenes.push_back(entry.path());
                        break;
                    case SolidUtils::FileType::FileType_Unknown:
                        project_assets.game_objects.push_back(entry.path());
                        break;
                    case SolidUtils::FileType::FileType_Texture:
                        project_assets.textures.push_back(entry.path());
                        break;
                    case SolidUtils::FileType::FileType_Model:
                        project_assets.meshes.push_back(entry.path());
                        break;
                    case SolidUtils::FileType::FileType_Material:
                        project_assets.materials.push_back(entry.path());
                        break;
                    case SolidUtils::FileType::FileType_Sound:
                        project_assets.audio.push_back(entry.path());
                        break;
                    default:
                        return;
                }
            }
        }
    }

    namespace ImGUIWindows {
        inline static void MainMenuBar(GLFWwindow* window, SolidScene* scene) {
            ImGui::PushStyleColor(ImGuiCol_Separator, colors["panel"]);
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("New Scene", "Ctrl+N")) {

                    }

                    if (ImGui::MenuItem("New Project", "Ctrl+Shift+N")) {

                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Open Scene...", "Ctrl+O")) {

                    }

                    if (ImGui::MenuItem("Open Project...", "Ctrl+Shift+O")) {

                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Save", "Ctrl+S")) {
                        char* path = WindowsDialogs::ShowSaveDialog(L"Save Scene", L"Solid Scene (*.scene)", WindowsDialogs::FileType::FileType_Scene);
                        if (path) {
                            scene->Save();
                            delete path;
                        }
                    }

                    if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {

                    }

                    if (ImGui::MenuItem("Save All", "Ctrl+Alt+S")) {

                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Build Settings", "F6")) {

                    }

                    if (ImGui::MenuItem("Build", "Ctrl+B")) {

                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Exit")) {
                        glfwSetWindowShouldClose(window, true);
                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Edit")) {
                    if (ImGui::MenuItem("Editor Preferences", "F2")) {
                        State::EditorPreferences::show_preferences = true;
                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Assets")) {
                    if (ImGui::MenuItem("Import")) {
                        // if (Dialogs::ShowOpenDialog(L"Import Asset") != nullptr) {
                        //     return;
                        // }
                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Window")) {
                    if (ImGui::MenuItem("Project")) {

                    }

                    if (ImGui::MenuItem("Scene")) {

                    }

                    if (ImGui::MenuItem("Inspector")) {

                    }

                    if (ImGui::MenuItem("Console")) {

                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Help")) {
                    if (ImGui::MenuItem("About")) {

                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMainMenuBar();
            }
            ImGui::PopStyleColor();

            if (State::EditorPreferences::show_preferences) {
                ImGui::OpenPopup(ICON_FA_WRENCH " Preferences");
            }

            ImGui::SetNextWindowContentSize(ImVec2(900, 500));
            ImGui::PushStyleColor(ImGuiCol_PopupBg, colors["panel"]);
            if (ImGui::BeginPopupModal(ICON_FA_WRENCH " Preferences", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Columns(2, "prefs_columns");
                ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() * 0.4f);
                ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() * 0.6f);

                if (ImGui::Selectable("General", State::EditorPreferences::selected_general, ImGuiSelectableFlags_SelectOnClick | ImGuiSelectableFlags_SpanAvailWidth)) {
                    State::EditorPreferences::selected_general = true;
                    State::EditorPreferences::selected_appearance = false;
                    State::EditorPreferences::selected_external_tools = false;
                }

                if (ImGui::Selectable("Appearance", State::EditorPreferences::selected_appearance, ImGuiSelectableFlags_SelectOnClick | ImGuiSelectableFlags_SpanAvailWidth)) {
                    State::EditorPreferences::selected_general = false;
                    State::EditorPreferences::selected_appearance = true;
                    State::EditorPreferences::selected_external_tools = false;
                }

                if (ImGui::Selectable("External Tools", State::EditorPreferences::selected_external_tools, ImGuiSelectableFlags_SelectOnClick | ImGuiSelectableFlags_SpanAvailWidth)) {
                    State::EditorPreferences::selected_general = false;
                    State::EditorPreferences::selected_appearance = false;
                    State::EditorPreferences::selected_external_tools = true;
                }

                ImGui::NextColumn();

                ImGui::Columns();

                if (ImGui::Button("Close")) {
                    State::EditorPreferences::show_preferences = false;
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
            ImGui::PopStyleColor();
        }

        inline static void Toolbar() {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar;
            ImGui::PushStyleColor(ImGuiCol_Separator, colors["panel"]);
            if (ImGui::BeginViewportSideBar("##toolbar", ImGui::GetMainViewport(), ImGuiDir_Up, ImGui::GetFrameHeight(), window_flags)) {
                if (ImGui::BeginMenuBar()) {
                    if (SolidUIComponents::ToggleButton(
                        ICON_FA_ARROWS_UP_DOWN_LEFT_RIGHT,
                        ImVec2(36, 24),
                        transformation_states[0],
                        colors["accent"],
                        colors["accent"],
                        colors["selected"],
                        colors["selected"]
                    )) {
                        transformation_states[0] = true;
                        transformation_states[1] = false;
                        transformation_states[2] = false;
                    }

                    if (SolidUIComponents::ToggleButton(
                        ICON_FA_ROTATE,
                        ImVec2(36, 24),
                        transformation_states[1],
                        colors["accent"],
                        colors["accent"],
                        colors["selected"],
                        colors["selected"]
                    )) {
                        transformation_states[0] = false;
                        transformation_states[1] = true;
                        transformation_states[2] = false;
                    }

                    if (SolidUIComponents::ToggleButton(
                        ICON_FA_MAXIMIZE,
                        ImVec2(36, 24),
                        transformation_states[2],
                        colors["accent"],
                        colors["accent"],
                        colors["selected"],
                        colors["selected"]
                    )) {
                        transformation_states[0] = false;
                        transformation_states[1] = false;
                        transformation_states[2] = true;
                    }

                    ImGui::Separator();

                    if (SolidUIComponents::ToggleButton(
                        ICON_FA_MAGNET,
                        ImVec2(36, 24),
                        grid_states[0],
                        colors["accent"],
                        colors["accent"],
                        colors["selected"],
                        colors["selected"]
                    )) {
                        grid_states[0] = !grid_states[0];
                    }

                    if (SolidUIComponents::ToggleButton(
                        ICON_FA_BORDER_ALL,
                        ImVec2(36, 24),
                        grid_states[1],
                        colors["accent"],
                        colors["accent"],
                        colors["selected"],
                        colors["selected"]
                    )) {
                        grid_states[1] = !grid_states[1];
                    }

                    ImGui::Separator();

                    if (SolidUIComponents::ToggleButton(
                        ICON_FA_SQUARE,
                        ImVec2(36, 24),
                        render_states[0],
                        colors["accent"],
                        colors["accent"],
                        colors["selected"],
                        colors["selected"]
                    )) {
                        render_states[0] = true;
                        render_states[1] = false;
                        render_states[2] = false;

                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    }

                    if (SolidUIComponents::ToggleButton(
                        ICON_FA_DICE_D6,
                        ImVec2(36, 24),
                        render_states[1],
                        colors["accent"],
                        colors["accent"],
                        colors["selected"],
                        colors["selected"]
                    )) {
                        render_states[0] = false;
                        render_states[1] = true;
                        render_states[2] = false;

                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    }

                    if (SolidUIComponents::ToggleButton(
                        ICON_FA_CUBES,
                        ImVec2(36, 24),
                        render_states[2],
                        colors["accent"],
                        colors["accent"],
                        colors["selected"],
                        colors["selected"]
                    )) {
                        render_states[0] = false;
                        render_states[1] = false;
                        render_states[2] = true;

                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    }

                    ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 56);
                    ImGui::BeginGroup();
                        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
                        if (ImGui::Button(ICON_FA_PLAY, ImVec2(36, 24))) {

                        }

                        if (ImGui::Button(ICON_FA_PAUSE, ImVec2(36, 24))) {

                        }

                        if (ImGui::Button(ICON_FA_FORWARD_FAST, ImVec2(36, 24))) {

                        }
                        ImGui::PopStyleVar();
                    ImGui::EndGroup();

                    ImGui::EndMenuBar();
                }

                ImGui::End();
            }
            ImGui::PopStyleColor();
        }

        inline static void Console() {
            ImGui::Begin(ICON_FA_CODE " Console");
                ImGui::BeginGroup();
                    if (ImGui::Button("Clear")) {
                        SolidLogger::GetInstance()->ClearLogs();
                    }

                    ImGui::SameLine();

                    // if (ImGui::Button("Pause")) {
                    //     if (SolidLogger::GetInstance()->IsLoggingPaused()) {
                    //         SolidLogger::GetInstance()->ResumeLogging();
                    //     } else {
                    //         SolidLogger::GetInstance()->PauseLogging();
                    //     }
                    // }

                    if (SolidUIComponents::ToggleButton(
                        "Pause",
                        ImVec2(42, 26),
                        State::Console::console_paused,
                        colors["accent"],
                        colors["accent"],
                        colors["selected"],
                        colors["selected"]
                    )) {
                        if (SolidLogger::GetInstance()->IsLoggingPaused()) {
                            SolidLogger::GetInstance()->ResumeLogging();
                            State::Console::console_paused = false;
                        } else {
                            SolidLogger::GetInstance()->PauseLogging();
                            State::Console::console_paused = true;
                        }
                    }

                    ImGui::SameLine();
                    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - 100.f);
                    ImGui::InputText("##console_search", console_search_buffer, IM_ARRAYSIZE(console_search_buffer));
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    ImGui::TextColored(colors["info"], "%d " ICON_FA_CIRCLE_EXCLAMATION, SolidLogger::GetInstance()->GetInfoCount());
                    ImGui::SameLine();
                    ImGui::TextColored(colors["warning"], "%d " ICON_FA_TRIANGLE_EXCLAMATION, SolidLogger::GetInstance()->GetWarningCount());
                    ImGui::SameLine();
                    ImGui::TextColored(colors["error"], "%d " ICON_FA_XMARK, SolidLogger::GetInstance()->GetErrorCount() + SolidLogger::GetInstance()->GetFatalCount());
                ImGui::EndGroup();
                
                ImGui::PushStyleColor(ImGuiCol_ChildBg, colors["panel"]);
                ImGui::BeginChild("##console_log", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
                    for (auto &log : SolidLogger::GetInstance()->GetLogs()) {
                        if (log.level == LogLevel::LogLevel_INFO) {
                            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                            ImGui::TextColored(colors["info"], ICON_FA_CIRCLE_EXCLAMATION);
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::BeginGroup();
                                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                                ImGui::TextColored(colors["info"], "[%s] %s", log.timestamp.c_str(), log.message);
                                ImGui::PopFont();
                            ImGui::EndGroup();
                            ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 36.0f);
                            if (ImGui::Button(ICON_FA_MESSAGE)) {
                                State::Console::log_entry = &log;
                            }
                        } else if (log.level == LogLevel::LogLevel_WARNING) {
                            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                            ImGui::TextColored(colors["warning"], ICON_FA_TRIANGLE_EXCLAMATION);
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::BeginGroup();
                                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                                ImGui::TextColored(colors["warning"], "[%s] %s", log.timestamp.c_str(), log.message);
                                ImGui::PopFont();
                                // ImGui::Text("%s (%d)", log.file, log.line);
                            ImGui::EndGroup();
                            ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 36.0f);
                            if (ImGui::Button(ICON_FA_MESSAGE)) {
                                State::Console::log_entry = &log;
                            }
                        } else if (log.level == LogLevel::LogLevel_ERROR) {
                            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                            ImGui::TextColored(colors["error"], ICON_FA_XMARK);
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::BeginGroup();
                                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                                ImGui::TextColored(colors["error"], "[%s] %s", log.timestamp.c_str(), log.message);
                                ImGui::PopFont();
                                // ImGui::Text("%s (%d)", log.file, log.line);
                            ImGui::EndGroup();
                            ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 36.0f);
                            if (ImGui::Button(ICON_FA_MESSAGE)) {
                                State::Console::log_entry = &log;
                            }
                        } else if (log.level == LogLevel::LogLevel_FATAL) {
                            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                            ImGui::TextColored(colors["error"], ICON_FA_XMARK);
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::BeginGroup();
                                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                                ImGui::TextColored(colors["error"], "[%s] %s", log.timestamp.c_str(), log.message);
                                ImGui::PopFont();
                                // ImGui::Text("%s (%d)", log.file, log.line);
                            ImGui::EndGroup();
                            ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 36.0f);
                            if (ImGui::Button(ICON_FA_MESSAGE)) {
                                State::Console::log_entry = &log;
                            }
                        }
                    }
                ImGui::EndChild();

                ImGui::Separator();

                ImGui::BeginChild("##console_details");

                    if (State::Console::log_entry != nullptr) {
                        ImGui::Text("%s", State::Console::log_entry->message);
                        ImGui::Text("%s (%d)", State::Console::log_entry->file, State::Console::log_entry->line);
                    }

                ImGui::EndChild();
                ImGui::PopStyleColor();
            ImGui::End();
        }

        inline static void Project(SolidProject &project) {
            ImGui::Begin(ICON_FA_FOLDER_CLOSED " Project");

            if (ImGui::TreeNode(ICON_FA_FILE_CODE " Scripts")) {
                for (int i = 0; i < project_assets.scripts.size(); i++) {
                    ImGui::PushID(i);
                    if (ImGui::Selectable(project_assets.scripts[i].filename().string().c_str(), false)) {}
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                        ImGui::SetDragDropPayload("Script", &i, sizeof(int));
                        ImGui::Text("%s", project_assets.scripts[i].filename().string().c_str());
                        ImGui::EndDragDropSource();
                    }
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }

            if (ImGui::TreeNode(ICON_FA_BRUSH " Materials")) {
                for (int i = 0; i < project_assets.materials.size(); i++) {
                    ImGui::PushID(i);
                    if (ImGui::Selectable(project_assets.materials[i].filename().string().c_str(), false)) {}
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                        ImGui::SetDragDropPayload("Material", &i, sizeof(int));
                        ImGui::Text("%s", project_assets.materials[i].filename().string().c_str());
                        ImGui::EndDragDropSource();
                    }
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }

            if (ImGui::TreeNode(ICON_FA_IMAGE " Textures")) {
                for (int i = 0; i < project_assets.textures.size(); i++) {
                    ImGui::PushID(i);
                    if (ImGui::Selectable(project_assets.textures[i].filename().string().c_str(), false)) {}
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                        ImGui::SetDragDropPayload("Texture", &i, sizeof(int));
                        ImGui::Text("%s", project_assets.textures[i].filename().string().c_str());
                        ImGui::EndDragDropSource();
                    }
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }

            if (ImGui::TreeNode(ICON_FA_SHAPES " Models")) {
                for (int i = 0; i < project_assets.meshes.size(); i++) {
                    ImGui::PushID(i);
                    if (ImGui::Selectable(project_assets.meshes[i].filename().string().c_str(), false)) {}
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                        ImGui::SetDragDropPayload("Model", &i, sizeof(int));
                        ImGui::Text("%s", project_assets.meshes[i].filename().string().c_str());
                        ImGui::EndDragDropSource();
                    }
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }

            if (ImGui::TreeNode(ICON_FA_FONT " Fonts")) {
                for (int i = 0; i < project_assets.fonts.size(); i++) {
                    ImGui::PushID(i);
                    if (ImGui::Selectable(project_assets.fonts[i].filename().string().c_str(), false)) {}
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                        ImGui::SetDragDropPayload("Font", &i, sizeof(int));
                        ImGui::Text("%s", project_assets.fonts[i].filename().string().c_str());
                        ImGui::EndDragDropSource();
                    }
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }

            if (ImGui::TreeNode(ICON_FA_MUSIC " Sounds")) {
                for (int i = 0; i < project_assets.audio.size(); i++) {
                    ImGui::PushID(i);
                    if (ImGui::Selectable(project_assets.audio[i].filename().string().c_str(), false)) {}
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                        ImGui::SetDragDropPayload("Audio", &i, sizeof(int));
                        ImGui::Text("%s", project_assets.audio[i].filename().string().c_str());
                        ImGui::EndDragDropSource();
                    }
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }

            if (ImGui::TreeNode(ICON_FA_MAP " Scenes")) {
                for (int i = 0; i < project_assets.scenes.size(); i++) {
                    ImGui::PushID(i);
                    if (ImGui::Selectable(project_assets.scenes[i].filename().string().c_str(), false)) {}
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                        ImGui::SetDragDropPayload("Scene", &i, sizeof(int));
                        ImGui::Text("%s", project_assets.scenes[i].filename().string().c_str());
                        ImGui::EndDragDropSource();
                    }
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }

            ImGui::End();
        }

        inline static void Scene(unsigned int sceneTexture) {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin(ICON_FA_IMAGE " Scene");
                ImGui::BeginChild("SceneTexture");
                    ImVec2 viewportSize = ImGui::GetWindowSize();

                    // Ignore this warning ''type cast': conversion from 'unsigned int' to 'void *' of greater size'
                    // ImGui uses void* to represent generic types, so we can just cast our texture id to void*
                    #pragma warning(suppress: 4312)
                    ImGui::Image((void*)sceneTexture, viewportSize, ImVec2(0, 1), ImVec2(1, 0));
                ImGui::EndChild();
            ImGui::End();
            ImGui::PopStyleVar();
        }

        inline static void Inspector(SolidScene *currentScene, SolidProject &project) {
            ImGui::Begin(ICON_FA_CUBE " Inspector");
                ImGui::PushStyleColor(ImGuiCol_Header, colors["menu"]);
                if (game_object_selected_id != 0) {
                    ImGui::Text(currentScene->GetGameObjects()[game_object_selected_id - 1]->mName);
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_TRASH " Delete")) {
                        currentScene->RemoveGameObject(game_object_selected_id);
                        game_object_selected_id = currentScene->GetGameObjects().size();
                    }
                    ImGui::Separator();
                    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
                        ImGui::Text("Position");
                        ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcItemWidth());
                        std::string labelID = "##Position" + std::to_string(game_object_selected_id);
                        SolidUIComponents::DragFloatN_Colored(
                            labelID.c_str(),
                            (float*)&currentScene->GetGameObjects()[game_object_selected_id - 1]->mTransform.mPosition,
                            3, 0.1f, -100.0f, 100.0f, "%.1f", 1.0f,
                            colors["error"], colors["success"], colors["info"]
                        );

                        ImGui::Text("Rotation");
                        ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcItemWidth());
                        labelID = "##Rotation" + std::to_string(game_object_selected_id);
                        SolidUIComponents::DragFloatN_Colored(
                            labelID.c_str(),
                            (float*)&currentScene->GetGameObjects()[game_object_selected_id - 1]->mTransform.mRotation,
                            3, 0.1f, -359.99f, 359.99f, "%.1f", 1.0f,
                            colors["error"], colors["success"], colors["info"]
                        );

                        ImGui::Text("Scale");
                        ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcItemWidth());
                        labelID = "##Scale" + std::to_string(game_object_selected_id);
                        SolidUIComponents::DragFloatN_Colored(
                            labelID.c_str(),
                            (float*)&currentScene->GetGameObjects()[game_object_selected_id - 1]->mTransform.mScale,
                            3, 0.1f, -100.0f, 100.0f, "%.1f", 1.0f,
                            colors["error"], colors["success"], colors["info"]
                        );
                    }
                    ImGui::Separator();

                    if (currentScene->GetGameObjects()[game_object_selected_id - 1]->GetType() == GO_Light) {
                        if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen)) {
                            ImGui::Text("Light properties");
                        }
                    }

                    for (const auto &component : currentScene->GetGameObjects()[game_object_selected_id - 1]->mComponents) {
                        if (component->GetType() == SolidComponentType::COM_Model) {
                            if (ImGui::CollapsingHeader(component->mName, ImGuiTreeNodeFlags_DefaultOpen)) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "Meshes (%d)", (int)dynamic_cast<SolidModel*>(component)->mMeshes.size());
                                if (ImGui::TreeNode(buf)) {
                                    unsigned int meshID = 0;
                                    for (auto &mesh : dynamic_cast<SolidModel*>(component)->mMeshes) {
                                        std::string labelID = mesh.GetName();
                                        if (ImGui::TreeNode(labelID.c_str())) {
                                            MaterialType materialType = mesh.GetMaterial()->GetType();
                                            std::string matTypes[] = { "Phong", "Unlit" };
                                            if (ImGui::TreeNode(("Material (" + matTypes[materialType] + ")##" + std::to_string(meshID)).c_str())) {
                                                if (mesh.GetMaterial()->GetType() == MaterialType::MAT_Phong) {
                                                    
                                                } else if (mesh.GetMaterial()->GetType() == MaterialType::MAT_Unlit) {
                                                    ImGui::Text("Color");
                                                    ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcItemWidth());
                                                    ImGui::ColorEdit4(
                                                        "Diffuse",
                                                        (float*)&dynamic_cast<UnlitMaterial*>(mesh.GetMaterial())->mDiffuse.color,
                                                        ImGuiColorEditFlags_NoLabel
                                                    );

                                                    ImGui::Text("Texture");
                                                    ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcItemWidth());
                                                    if (SolidUIComponents::DragDropTarget(ProjectItemType::ProjectItemType_File_Texture, ImVec2(ImGui::GetContentRegionAvail().x, 24.f))) {
                                                        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("Texture")) {
                                                            int id = *(int*)payload->Data;
                                                            std::filesystem::path texPath = project_assets.textures[id];

                                                            unsigned int texID;
                                                            unsigned int* texIdPtr = dynamic_cast<UnlitMaterial*>(mesh.GetMaterial())->mDiffuse.texture;

                                                            if (texIdPtr == nullptr) {
                                                                texID = SolidUtils::LoadTexture(texPath.string().c_str());
                                                                dynamic_cast<UnlitMaterial*>(mesh.GetMaterial())->mDiffuse.texture = &texID;
                                                            } else {
                                                                texID = SolidUtils::UpdateTexture(texPath.string().c_str(), *texIdPtr);
                                                                dynamic_cast<UnlitMaterial*>(mesh.GetMaterial())->mDiffuse.texture = &texID;
                                                            }
                                                        }

                                                        ImGui::EndDragDropTarget();
                                                    }

                                                    if (ImGui::Button("Save")) {
                                                        SolidMaterial::Serialize(std::string(project.GetProjectPath()), "Test", dynamic_cast<UnlitMaterial*>(mesh.GetMaterial()));
                                                    }
                                                }

                                                ImGui::TreePop();
                                            }
                                            ImGui::TreePop();
                                        }
                                        meshID++;
                                    }

                                    ImGui::TreePop();
                                }
                            }
                        }
                    }
                }
                ImGui::PopStyleColor();
            ImGui::End();
        }

        inline static void SceneHierarchy(SolidScene *currentScene) {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin(ICON_FA_LIST " Hierarchy");
            
                ImGui::PushStyleColor(ImGuiCol_ChildBg, colors["panel"]);
                ImGui::SetCursorPosX(4.0f); // 4px padding from border
                ImGui::BeginChild("##Hierarchy", ImVec2(ImGui::GetWindowContentRegionWidth() - 8, ImGui::GetContentRegionAvail().y), false);
                    ImGui::PushStyleColor(ImGuiCol_HeaderActive, colors["accent"]);
                    for (auto& gameObject : currentScene->GetGameObjects()) {
                        if (ImGui::Selectable(gameObject->mName, game_object_selected_id == gameObject->GetID())) {
                            game_object_selected_id = gameObject->GetID();
                        }
                    }
                    ImGui::PopStyleColor();
                ImGui::EndChild();
                ImGui::PopStyleColor();

                if (ImGui::BeginDragDropTarget()) {
                    if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("Model")) {
                        int id = *(int*)payload->Data;
                        std::filesystem::path modelPath = project_assets.meshes[id];
                        std::string modelPathStr = modelPath.string();
                        std::string name = modelPath.stem().string();

                        // Need to copy because pointer to name is lost after the loop
                        // https://www.techiedelight.com/convert-std-string-char-cpp/
                        char* nameStr = strcpy(new char[name.length() + 1], name.c_str());

                        SolidModel *model = new SolidModel((char*)modelPathStr.c_str());
                        SolidGameObject *gameObject = new SolidGameObject(nameStr, SolidGameObjectType::GO_GameObject);
                        gameObject->AddComponent<SolidModel>(model);
                        currentScene->AddGameObject(gameObject);
                    }

                    ImGui::EndDragDropTarget();
                }
            ImGui::End();
            ImGui::PopStyleVar();
        }

        inline static void Analytics() {
            ImGui::Begin(ICON_FA_STOPWATCH " Analytics");
                float framerate = ImGui::GetIO().Framerate;
                float frametime = ImGui::GetIO().Framerate > 0 ? 1000.f / framerate : 0.f;
                std::string gpu_renderer = SolidProfiler::GPU::GetRenderer(); // this probably doesn't need to be created every frame
                float used_memory = std::get<1>(SolidProfiler::GPU::GetMemoryUsage());
                float total_memory = std::get<0>(SolidProfiler::GPU::GetMemoryUsage());

                float usedVirtualMem = static_cast<int>(std::get<0>(SolidProfiler::Process::GetProcessMemoryUsage())) / 1000000.f;
                float usedPhysMem = static_cast<int>(std::get<1>(SolidProfiler::Process::GetProcessMemoryUsage())) / 1000000.f;
                float cpuUsage = static_cast<float>(SolidProfiler::Process::GetProcessCPUUsage());

                char fps[10];
                char ms[10];
                char used_memory_str[100];
                char total_memory_str[100];
                char used_virtual_mem_str[100];
                char used_phys_mem_str[100];
                char cpu_usage_str[100];

                snprintf(fps, sizeof(fps), "%.1f", framerate);
                snprintf(ms, sizeof(ms), "%.1f", frametime);
                snprintf(used_memory_str, sizeof(used_memory_str), "%.1f", used_memory);
                snprintf(total_memory_str, sizeof(total_memory_str), "%.1f", total_memory);
                snprintf(used_virtual_mem_str, sizeof(used_virtual_mem_str), "%.1f", usedVirtualMem);
                snprintf(used_phys_mem_str, sizeof(used_phys_mem_str), "%.1f", usedPhysMem);
                snprintf(cpu_usage_str, sizeof(cpu_usage_str), "%.1f", cpuUsage);

                ImGui::Text("GPU:");
                ImGui::SameLine(ImGui::GetContentRegionAvail().x - (ImGui::CalcTextSize(gpu_renderer.c_str()).x - ImGui::CalcTextSize("  ").x));
                ImGui::Text("%s", gpu_renderer.c_str());

                ImGui::Separator();

                ImGui::Text("Framerate:");
                ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(fps).x);
                if (framerate >= 59.f) {
                    ImGui::TextColored(colors["success"], "%.2f", framerate);
                } else if (framerate >= 30.f) {
                    ImGui::TextColored(colors["warning"], "%.2f", framerate);
                } else {
                    ImGui::TextColored(colors["error"], "%.2f", framerate);
                }

                ImGui::Separator();

                ImGui::Text("Frame Time:");
                ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(ms).x);
                if (frametime <= 16.94f) {
                    ImGui::TextColored(colors["success"], "%.2f", frametime);
                } else if (frametime <= 33.33f) {
                    ImGui::TextColored(colors["warning"], "%.2f", frametime);
                } else {
                    ImGui::TextColored(colors["error"], "%.2f", frametime);
                }

                ImGui::Separator();

                float gpu_memory_usage = used_memory / total_memory;

                ImGui::Text("Memory (used):");
                ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(used_memory_str).x);
                if (gpu_memory_usage <= 0.75f) {
                    ImGui::TextColored(colors["success"], "%.2f MB", used_memory / 1000.f);
                } else if (gpu_memory_usage <= 0.9f) {
                    ImGui::TextColored(colors["warning"], "%.2f MB", used_memory / 1000.f);
                } else {
                    ImGui::TextColored(colors["error"], "%.2f MB", used_memory / 1000.f);
                }

                ImGui::Separator();

                ImGui::Text("Memory (total):");
                ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(total_memory_str).x);
                ImGui::Text("%.2f MB", total_memory / 1000.f);

                ImGui::Separator();

                ImGui::Text("Virtual Memory (used):");
                ImGui::SameLine(ImGui::GetContentRegionAvail().x - (ImGui::CalcTextSize(used_virtual_mem_str).x + ImGui::CalcTextSize(" MB").x));
                ImGui::Text("%.2f MB", usedVirtualMem);

                ImGui::Separator();

                ImGui::Text("RAM (used):");
                ImGui::SameLine(ImGui::GetContentRegionAvail().x - (ImGui::CalcTextSize(used_phys_mem_str).x + ImGui::CalcTextSize(" MB").x));
                ImGui::Text("%.2f MB", usedPhysMem);

                ImGui::Separator();

                ImGui::Text("CPU Usage:");
                ImGui::SameLine(ImGui::GetContentRegionAvail().x - (ImGui::CalcTextSize(cpu_usage_str).x + ImGui::CalcTextSize(" %").x));
                ImGui::Text("%.2f%", cpuUsage);

            ImGui::End();
        }
    }

    inline static void InitUI(GLFWwindow* window, SolidProject &project) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;
        
        Helpers::LoadColors("Default");
        Helpers::ApplyColors();
        Helpers::LoadFonts(io);

        Helpers::ParseProjectAssets(project);

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    inline static void DrawUI(GLFWwindow* window, unsigned int sceneTexture, SolidProject &project) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGUIWindows::MainMenuBar(window, project.GetActiveScene());
        ImGUIWindows::Toolbar();
        ImGUIWindows::Console();
        ImGUIWindows::Project(project);
        ImGUIWindows::Scene(sceneTexture);
        ImGUIWindows::Inspector(project.GetActiveScene(), project);
        ImGUIWindows::SceneHierarchy(project.GetActiveScene());
        ImGUIWindows::Analytics();
    }

    inline static void RenderUI() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    inline static void ShutdownUI() {

    }

    inline static void ApplyTheme(const std::string& themeName) {
        Helpers::LoadColors(themeName);
        Helpers::ApplyColors();
    }
}