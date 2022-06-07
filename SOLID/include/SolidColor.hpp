#pragma once

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <string>

/**
 * @brief General purpose color class
 * 
 * I needed something extremely easy and robust to work with
 * so this provides all the color functions needed.
 * 
 * @example SolidColor c = SolidColor(1.0f, 0.0f, 0.0f, 1.0f);
 * @example SolidColor c = SolidColor("FF00E7");
 * @example SolidColor c = SolidColor(128);
 * 
 * @note Colors are stored as floats in the range [0,1]
 * Values passed that are outside this range will be converted
 * by dividing by 255.
 */
struct SolidColor {
    float r, g, b, a;

    SolidColor();
    SolidColor(float r, float g, float b, float a);
    SolidColor(float r, float g, float b);
    SolidColor(float n);
    SolidColor(int r, int g, int b, int a);
    SolidColor(int r, int g, int b);
    SolidColor(int n);
    SolidColor(double r, double g, double b, double a);
    SolidColor(double r, double g, double b);
    SolidColor(const char* hex);
    SolidColor(const char* hex, float a);
    SolidColor(std::string hex);
    SolidColor(std::string hex, float a);
    SolidColor(ImVec4 color);
    SolidColor(glm::vec4 color);
    SolidColor(glm::vec3 color);
    SolidColor(const SolidColor& c);

    bool operator==(const SolidColor& c) const;
    bool operator!=(const SolidColor& c) const;
    bool operator<(const SolidColor& c) const;
    bool operator>(const SolidColor& c) const;
    bool operator<=(const SolidColor& c) const;
    bool operator>=(const SolidColor& c) const;
};