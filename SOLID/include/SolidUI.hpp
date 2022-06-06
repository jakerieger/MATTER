#pragma once

#include <stdio.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <map>

#include <imgui/IconsFontAwesome6.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <pugixml.hpp>

#include "SolidUtils.hpp"
#include "SolidLogger.hpp"
#include "SolidProfiler.hpp"
#include "SolidUIComponents.hpp"
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

    // This is confusing variable naming, but it's just a way to keep track of the current state of the console UI
    static bool console_item_selected = false;
    static unsigned int console_selected_item = 0;

    inline static std::map<std::string, ImVec4> GetColors() { return colors; }

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
            styleColors[ImGuiCol_ChildBg]                = colors["panel"];
            styleColors[ImGuiCol_PopupBg]                = colors["panel"];
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
            styleColors[ImGuiCol_HeaderHovered]          = colors["selected"];
            styleColors[ImGuiCol_HeaderActive]           = colors["selected"];
            styleColors[ImGuiCol_Separator]              = SolidUtils::ChangeColorAlpha(styleColors[ImGuiCol_Border], 0.67f);
            styleColors[ImGuiCol_SeparatorHovered]       = colors["accent"];
            styleColors[ImGuiCol_SeparatorActive]        = colors["accent"];
            styleColors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
            styleColors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
            styleColors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
            styleColors[ImGuiCol_Tab]                    = styleColors[ImGuiCol_Header];
            styleColors[ImGuiCol_TabHovered]             = styleColors[ImGuiCol_HeaderHovered];
            styleColors[ImGuiCol_TabActive]              = styleColors[ImGuiCol_HeaderActive];
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
            styleColors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
            styleColors[ImGuiCol_NavHighlight]           = ImVec4(30.f / 255.f, 30.f / 255.f, 30.f / 255.f, 1.00f);
            styleColors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            styleColors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            styleColors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.00f, 0.00f, 0.00f, 0.6f);
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
    }

    namespace ImGUIWindows {
        inline static void MainMenuBar() {
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("New")) {

                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Edit")) {
                    if (ImGui::MenuItem("Undo")) {

                    }

                    if (ImGui::MenuItem("Redo")) {

                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Cut")) {

                    }

                    if (ImGui::MenuItem("Copy")) {

                    }

                    if (ImGui::MenuItem("Paste")) {

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
        }

        inline static void Toolbar() {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar;
            if (ImGui::BeginViewportSideBar("##toolbar", ImGui::GetMainViewport(), ImGuiDir_Up, ImGui::GetFrameHeightWithSpacing(), window_flags)) {
                if (ImGui::BeginMenuBar()) {
                    if (ImGui::Button(ICON_FA_ARROWS_UP_DOWN_LEFT_RIGHT, ImVec2(36, 36))) {

                    }

                    if (ImGui::Button(ICON_FA_ROTATE, ImVec2(36, 36))) {

                    }

                    if (ImGui::Button(ICON_FA_MAXIMIZE, ImVec2(36, 36))) {

                    }

                    if (ImGui::Button(ICON_FA_MAGNET, ImVec2(36, 36))) {

                    }

                    if (ImGui::Button(ICON_FA_CUBES, ImVec2(36, 36))) {

                    }

                    ImGui::EndMenuBar();
                }

                ImGui::End();
            }
        }

        inline static void Console(SolidLogger &logger) {
            ImGui::Begin(ICON_FA_CODE " Console");
                ImGui::BeginGroup();
                    if (ImGui::Button("Clear")) {
                        logger.ClearLogs();
                    }

                    ImGui::SameLine();

                    if (ImGui::Button("Pause")) {
                        if (logger.IsLoggingPaused()) {
                            logger.ResumeLogging();
                        } else {
                            logger.PauseLogging();
                        }
                    }

                    ImGui::SameLine();
                    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - 100.f);
                    ImGui::InputText("##console_search", console_search_buffer, IM_ARRAYSIZE(console_search_buffer));
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    ImGui::TextColored(colors["info"], "%d " ICON_FA_CIRCLE_EXCLAMATION, logger.GetInfoCount());
                    ImGui::SameLine();
                    ImGui::TextColored(colors["warning"], "%d " ICON_FA_TRIANGLE_EXCLAMATION, logger.GetWarningCount());
                    ImGui::SameLine();
                    ImGui::TextColored(colors["error"], "%d " ICON_FA_XMARK, logger.GetErrorCount() + logger.GetFatalCount());
                ImGui::EndGroup();
                
                ImGui::BeginChild("##console_log", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
                    for (int i = 0; i < logger.GetLogs().size(); i++) {
                        LogEntry &log = logger.GetLogs()[i];
                        if (log.level == LogLevel::INFO) {
                            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                            ImGui::TextColored(colors["info"], ICON_FA_CIRCLE_EXCLAMATION);
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::BeginGroup();
                                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                                ImGui::TextColored(colors["info"], "[%s] %s", log.timestamp.c_str(), log.message);
                                ImGui::PopFont();
                                ImGui::Text("%s (%d)", log.file, log.line);
                            ImGui::EndGroup();
                        } else if (log.level == LogLevel::WARNING) {
                            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                            ImGui::TextColored(colors["warning"], ICON_FA_TRIANGLE_EXCLAMATION);
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::BeginGroup();
                                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                                ImGui::TextColored(colors["warning"], "[%s] %s", log.timestamp.c_str(), log.message);
                                ImGui::PopFont();
                                ImGui::Text("%s (%d)", log.file, log.line);
                            ImGui::EndGroup();
                        } else if (log.level == LogLevel::ERROR) {
                            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                            ImGui::TextColored(colors["error"], ICON_FA_XMARK);
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::BeginGroup();
                                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                                ImGui::TextColored(colors["error"], "[%s] %s", log.timestamp.c_str(), log.message);
                                ImGui::PopFont();
                                ImGui::Text("%s (%d)", log.file, log.line);
                            ImGui::EndGroup();
                        } else if (log.level == LogLevel::FATAL) {
                            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                            ImGui::TextColored(colors["error"], ICON_FA_XMARK);
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::BeginGroup();
                                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                                ImGui::TextColored(colors["error"], "[%s] %s", log.timestamp.c_str(), log.message);
                                ImGui::PopFont();
                                ImGui::Text("%s (%d)", log.file, log.line);
                            ImGui::EndGroup();
                        }
                    }
                ImGui::EndChild();

                ImGui::PushStyleColor(ImGuiCol_ChildBg, colors["menu"]);
                ImGui::BeginChild("##console_details");

                ImGui::EndChild();
                ImGui::PopStyleColor();
            ImGui::End();
        }

        inline static void Project() {
            ImGui::Begin(ICON_FA_FOLDER_CLOSED " Project");

            ImGui::End();
        }

        inline static void Scene(unsigned int sceneTexture) {
            ImGui::Begin(ICON_FA_IMAGE " Scene");
                ImGui::BeginChild("SceneTexture");
                    ImVec2 viewportSize = ImGui::GetWindowSize();

                    // Ignore this warning ''type cast': conversion from 'unsigned int' to 'void *' of greater size'
                    // ImGui uses void* to represent generic types, so we can just cast our texture id to void*
                    #pragma warning(suppress: 4312)
                    ImGui::Image((void*)sceneTexture, viewportSize, ImVec2(0, 1), ImVec2(1, 0));
                ImGui::EndChild();
            ImGui::End();
        }

        inline static void Inspector() {
            ImGui::Begin(ICON_FA_CUBE " Inspector");

            ImGui::End();
        }

        inline static void SceneHierarchy() {
            ImGui::Begin(ICON_FA_DIAGRAM_PROJECT " Hierarchy");

            ImGui::End();
        }

        inline static void Analytics() {
            ImGui::Begin(ICON_FA_STOPWATCH " Analytics");
                float framerate = ImGui::GetIO().Framerate;
                float frametime = ImGui::GetIO().Framerate > 0 ? 1000.f / framerate : 0.f;
                std::string gpu_renderer = SolidProfiler::GPU::GetRenderer(); // this probably doesn't need to be created every frame
                float used_memory = std::get<1>(SolidProfiler::GPU::GetMemoryUsage());
                float total_memory = std::get<0>(SolidProfiler::GPU::GetMemoryUsage());

                ImGui::Text("Framerate:");
                ImGui::SameLine();
                if (framerate >= 59.f) {
                    ImGui::TextColored(colors["success"], "%.2f", framerate);
                } else if (framerate >= 30.f) {
                    ImGui::TextColored(colors["warning"], "%.2f", framerate);
                } else {
                    ImGui::TextColored(colors["error"], "%.2f", framerate);
                }

                ImGui::Text("Frame Time:");
                ImGui::SameLine();
                if (frametime <= 16.94f) {
                    ImGui::TextColored(colors["success"], "%.2f", frametime);
                } else if (frametime <= 33.33f) {
                    ImGui::TextColored(colors["warning"], "%.2f", frametime);
                } else {
                    ImGui::TextColored(colors["error"], "%.2f", frametime);
                }

                float gpu_memory_usage = used_memory / total_memory;

                ImGui::Text("GPU:");
                ImGui::SameLine();
                ImGui::Text("%s", gpu_renderer.c_str());

                ImGui::Text("Memory (used):");
                ImGui::SameLine();
                if (gpu_memory_usage <= 0.75f) {
                    ImGui::TextColored(colors["success"], "%.2f MB", used_memory / 1000.f);
                } else if (gpu_memory_usage <= 0.9f) {
                    ImGui::TextColored(colors["warning"], "%.2f MB", used_memory / 1000.f);
                } else {
                    ImGui::TextColored(colors["error"], "%.2f MB", used_memory / 1000.f);
                }

                ImGui::Text("Memory (total):");
                ImGui::SameLine();
                ImGui::Text("%.2f MB", total_memory / 1000.f);

            ImGui::End();
        }
    }

    inline static void InitUI(GLFWwindow* window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;
        
        Helpers::LoadColors("Pro");
        Helpers::ApplyColors();
        Helpers::LoadFonts(io);

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    inline static void DrawUI(unsigned int sceneTexture, SolidLogger &logger) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGUIWindows::MainMenuBar();
        ImGUIWindows::Toolbar();
        ImGUIWindows::Console(logger);
        ImGUIWindows::Project();
        ImGUIWindows::Scene(sceneTexture);
        ImGUIWindows::Inspector();
        ImGUIWindows::SceneHierarchy();
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