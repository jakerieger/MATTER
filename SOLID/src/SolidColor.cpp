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

#include "SolidColor.hpp"

SolidColor::SolidColor() : r(0), g(0), b(0), a(1) {}
SolidColor::SolidColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
SolidColor::SolidColor(float r, float g, float b) : r(r), g(g), b(b), a(1) {}
SolidColor::SolidColor(float n) : r(n), g(n), b(n), a(1) {}
SolidColor::SolidColor(int r, int g, int b, int a) : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}
SolidColor::SolidColor(int r, int g, int b) : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(1) {}
SolidColor::SolidColor(int n) : r(n / 255.0f), g(n / 255.0f), b(n / 255.0f), a(1) {}
SolidColor::SolidColor(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}
SolidColor::SolidColor(double r, double g, double b) : r(r), g(g), b(b), a(1) {}

SolidColor::SolidColor(const char* hex) {
    int _r, _g, _b;
    sscanf(hex, "%02x%02x%02x", &_r, &_g, &_b);
    _r /= 255.0f;
    _g /= 255.0f;
    _b /= 255.0f;
    this->r = _r;
    this->g = _g;
    this->b = _b;
    this->a = 1.0f;
}

SolidColor::SolidColor(const char* hex, float a) : a(a) {
    int _r, _g, _b;
    sscanf(hex, "%02x%02x%02x", &_r, &_g, &_b);
    _r /= 255.0f;
    _g /= 255.0f;
    _b /= 255.0f;
    this->r = _r;
    this->g = _g;
    this->b = _b;
}

SolidColor::SolidColor(std::string hex) {
    int _r, _g, _b;
    sscanf(hex.c_str(), "%02x%02x%02x", &_r, &_g, &_b);
    _r /= 255.0f;
    _g /= 255.0f;
    _b /= 255.0f;
    this->r = _r;
    this->g = _g;
    this->b = _b;
    this->a = 1.0f;
}

SolidColor::SolidColor(std::string hex, float a) : a(a) {
    int _r, _g, _b;
    sscanf(hex.c_str(), "%02x%02x%02x", &_r, &_g, &_b);
    _r /= 255.0f;
    _g /= 255.0f;
    _b /= 255.0f;
    this->r = _r;
    this->g = _g;
    this->b = _b;
}

SolidColor::SolidColor(ImVec4 color) : r(color.x), g(color.y), b(color.z), a(color.w) {}
SolidColor::SolidColor(glm::vec4 color) : r(color.x), g(color.y), b(color.z), a(color.w) {}
SolidColor::SolidColor(glm::vec3 color) : r(color.x), g(color.y), b(color.z), a(1.0f) {}
SolidColor::SolidColor(const SolidColor& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

bool SolidColor::operator== (const SolidColor& c) const {
    return r == c.r && g == c.g && b == c.b && a == c.a;
}

bool SolidColor::operator> (const SolidColor& c) const {
    return r > c.r && g > c.g && b > c.b && a > c.a;
}

bool SolidColor::operator< (const SolidColor& c) const {
    return r < c.r && g < c.g && b < c.b && a < c.a;
}

bool SolidColor::operator<= (const SolidColor& c) const {
    return r <= c.r && g <= c.g && b <= c.b && a <= c.a;
}

bool SolidColor::operator>= (const SolidColor& c) const {
    return r >= c.r && g >= c.g && b >= c.b && a >= c.a;
}