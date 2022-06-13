#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <istream>
#include <map>

#include <glad/glad.h>
#include <imgui/IconsFontAwesome6.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <pugixml.hpp>
#include <nlohmann/json.hpp>

#include <SolidUtils.hpp>

using JSON = nlohmann::json;

namespace HubUI {
    static std::string theme = "Default";
    static std::map<std::string, ImVec4> colors {
        { "panel",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "scene",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "frame",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "accent",        ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "border",        ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "text",          ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "text_inactive", ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "button",        ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "button_hover",  ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "selected",      ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "header",        ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "menu",          ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "success",       ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "warning",       ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "error",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "xaxis",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "yaxis",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
        { "zaxis",         ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
    };
    static float window_rounding = 0.0f;
    static float frame_rounding = 0.0f;
    static float border_size = 1.0f;

    inline static std::map<std::string, ImVec4>& GetColors() {
        return colors;
    }

    namespace State {
        static unsigned int current_window = 0;
    }

    namespace Helpers {
        inline static void ReadEditorConfig() {
            if (std::filesystem::exists(SolidUtils::GetEditorConfigPath())) {
                std::ifstream configFile(SolidUtils::GetEditorConfigPath());
                JSON config;
                configFile >> config;
                configFile.close();

                theme = config["generalPreferences"]["theme"];
            }
        }

        inline static void LoadTheme() {
            std::string defaultTheme = SolidUtils::GetEditorThemesPath() + "\\" + theme + ".xml";
            pugi::xml_document themeDoc;
            pugi::xml_parse_result result = themeDoc.load_file(defaultTheme.c_str());

            if (!result)
                std::cout << "Error loading theme: " << result.description() << std::endl;

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
            styleColors[ImGuiCol_Button]                 = colors["button"];
            styleColors[ImGuiCol_ButtonHovered]          = colors["button_hover"];
            styleColors[ImGuiCol_ButtonActive]           = colors["button"];
            styleColors[ImGuiCol_Header]                 = colors["header"];
            styleColors[ImGuiCol_HeaderHovered]          = colors["header"];
            styleColors[ImGuiCol_HeaderActive]           = colors["header"];
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
            io.Fonts->AddFontFromFileTTF((SolidUtils::GetEditorFontsPath() + "/TitilliumWeb-Regular.ttf").c_str(), 22.0f);

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

    namespace Components {
        inline static bool ButtonPrimary(const char* label, ImVec2 size) {
            bool clicked = false;
            ImGui::PushStyleColor(ImGuiCol_Button, colors["accent"]);

            ImVec4 buttonHovCol = ImVec4(colors["accent"].x + 0.1f, colors["accent"].y + 0.1f, colors["accent"].z + 0.1f, colors["accent"].w);

            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonHovCol);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors["accent"]);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_Border, colors["accent"]);

            clicked |= ImGui::Button(label, size);

            ImGui::PopStyleColor(5);

            return clicked;
        }
    }

    namespace Windows {
        inline static void Projects() {
            ImGui::Begin("main", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::Text("Projects");

            ImGui::SameLine(ImGui::GetContentRegionAvail().x - 200.f);

            if (ImGui::Button("Add", ImVec2(100, 36))) {

            }

            ImGui::SameLine();

            if (Components::ButtonPrimary("New Project", ImVec2(100, 36))) {
                State::current_window = 1;
            }

            ImGui::Separator();

            ImGui::BeginTable("Projects", 3, ImGuiTableFlags_Resizable);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 100.f);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 100.f);
            ImGui::TableSetupColumn("Status", ImGuiTableColumnFlags_WidthFixed, 100.f);
            ImGui::EndTable();

            ImGui::End();
        }

        inline static void NewProject() {
            ImGui::Begin("newproject", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::Text("New Project");

            ImGui::End();
        }

        inline static void Settings() {
            ImGui::Begin("settings", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::Text("Settings");

            ImGui::End();
        }
    }

    inline static void Init(GLFWwindow* window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        
        Helpers::ReadEditorConfig();
        Helpers::LoadTheme();
        Helpers::LoadFonts(io);

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    inline static void Draw() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        switch (State::current_window) {
            case 0:
                Windows::Projects();
                break;
            case 1:
                Windows::NewProject();
                break;
            case 2:
                Windows::Settings();
                break;
            default:
                Windows::Projects();
                break;
        }

        ImGui::PopStyleVar(2);
    }

    inline static void Render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}