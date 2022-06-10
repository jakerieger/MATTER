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

#include <stb_image.h>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <stdio.h>

/**
 * @brief Utility functions use by other SOLID classes
 * 
 * Adding new functions is safe but changing existing functions is not recommended as many SOLID classes rely on these functions.
 * 
 * @note This namespace is not really meant to be used by the user.
 * @author Jake Rieger
 */
namespace SolidUtils {
    enum FileType {
        FileType_Unknown,
        FileType_Script,
        FileType_Material,
        FileType_Texture,
        FileType_Model,
        FileType_Font,
        FileType_Sound,
        FileType_Scene,
        FileType_Project,
    };

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

    inline static ImVec4 ChangeColorAlpha(ImVec4 color, float alpha) {
        ImVec4 colorVec = { color.x, color.y, color.z, alpha };
        return colorVec;
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

    inline static FileType GetFileType(std::string ext) {
        if (ext == ".cs") {
            return FileType_Script;
        } else if (ext == ".mat") {
            return FileType_Material;
        } else if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp" || ext == ".tga" || ext == ".hdr") {
            return FileType_Texture;
        } else if (ext == ".fbx" || ext == ".obj" || ext == ".dae") {
            return FileType_Model;
        } else if (ext == ".ttf" || ext == ".otf") {
            return FileType_Font;
        } else if (ext == ".wav" || ext == ".mp3" || ext == ".ogg") {
            return FileType_Sound;
        } else if (ext == ".scene") {
            return FileType_Scene;
        } else if (ext == ".solid") {
            return FileType_Project;
        } else {
            return FileType_Unknown;
        }
    }

    inline static unsigned int LoadTexture(const char* path) {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data) {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        } else {
            printf("Failed to load texture");
            stbi_image_free(data);
        }

        return textureID;
    }

    inline static unsigned int ColorVecToIMU32(ImVec4 color) {
        unsigned int r = (unsigned int)(color.x * 255);
        unsigned int g = (unsigned int)(color.y * 255);
        unsigned int b = (unsigned int)(color.z * 255);
        unsigned int a = 255;

        unsigned int colorUint = (a << 24) | (b << 16) | (g << 8) | r;
        return colorUint;
    };
}