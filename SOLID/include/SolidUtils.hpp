#pragma once

#include <imgui/imgui.h>
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>

namespace SolidUtils {
    inline static std::string GetResourcesPath() {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::filesystem::path resourcesPath = cwd / "resources";
        return resourcesPath.string();
    }

    inline static std::string GetEditorFontsPath() {
        std::string resourcesPath = GetResourcesPath();
        std::string editorFontsPath = resourcesPath + "\\interface\\fonts";
        return editorFontsPath;
    }

    inline static std::string GetEditorShadersPath() {
        std::string resourcesPath = GetResourcesPath();
        std::string editorShadersPath = resourcesPath + "\\shaders";
        return editorShadersPath;
    }

    inline static std::string GetEditorGizmosPath() {
        std::string resourcesPath = GetResourcesPath();
        std::string editorGizmosPath = resourcesPath + "\\interface\\gizmos";
        return editorGizmosPath;
    }

    inline static std::string GetEditorThemesPath() {
        std::string resourcesPath = GetResourcesPath();
        std::string editorThemesPath = resourcesPath + "\\interface\\themes";
        return editorThemesPath;
    }

    inline static std::string GetEditorConfigPath() {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::filesystem::path editorConfigPath = cwd / "solid.json";
        return editorConfigPath.string();
    }

    inline static ImVec4 ColorVecFromHex(const char* hex, float alpha = 1.0f) {
        ImVec4 color;
        int r, g, b;
        sscanf(hex, "%02x%02x%02x", &r, &g, &b);
        
        color.x = (float)r / 255.0f;
        color.y = (float)g / 255.0f;
        color.z = (float)b / 255.0f;
        color.w = alpha;

        return color;
    }

    inline static std::string GetTimestamp() {
        time_t rawtime;
        struct tm* timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, 80, "%I:%M %p", timeinfo);
        puts(buffer);

        std::string timestamp;
        timestamp += buffer;

        return timestamp;
    }
}