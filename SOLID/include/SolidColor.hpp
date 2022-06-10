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

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <string>
#include <msgpack.hpp>

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
    MSGPACK_DEFINE(r, g, b, a);

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