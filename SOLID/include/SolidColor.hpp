#include <imgui/imgui.h>
#include <glm/glm.hpp>

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
    SolidColor(ImVec3 color);
    SolidColor(glm::vec4 color);
    SolidColor(glm::vec3 color);
    SolidColor(const SolidColor& c);

    SolidColor& operator=(const SolidColor& c);
    SolidColor& operator+=(const SolidColor& c);
    SolidColor& operator-=(const SolidColor& c);
    SolidColor& operator*=(const SolidColor& c);
    SolidColor& operator/=(const SolidColor& c);
    SolidColor& operator*=(float f);
    SolidColor& operator/=(float f);
    SolidColor operator+(const SolidColor& c) const;
    SolidColor operator-(const SolidColor& c) const;
    SolidColor operator*(const SolidColor& c) const;
    SolidColor operator/(const SolidColor& c) const;
    SolidColor operator*(float f) const;
    SolidColor operator/(float f) const;
    bool operator==(const SolidColor& c) const;
    bool operator!=(const SolidColor& c) const;
    bool operator<(const SolidColor& c) const;
    bool operator>(const SolidColor& c) const;
    bool operator<=(const SolidColor& c) const;
    bool operator>=(const SolidColor& c) const;
};

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
    _a = 1.0f;
    this->r = _r;
    this->g = _g;
    this->b = _b;
    this->a = _a;
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
    _a = 1.0f;
    this->r = _r;
    this->g = _g;
    this->b = _b;
    this->a = _a;
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
SolidColor::SolidColor(ImVec3 color) : r(color.x), g(color.y), b(color.z), a(1.0f) {}
SolidColor::SolidColor(glm::vec4 color) : r(color.x), g(color.y), b(color.z), a(color.w) {}
SolidColor::SolidColor(glm::vec3 color) : r(color.x), g(color.y), b(color.z), a(1.0f) {}
SolidColor::SolidColor(const SolidColor& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

SolidColor::operator/ (const SolidColor& c) const {
    return SolidColor(r / c.r, g / c.g, b / c.b, a / c.a);
}

SolidColor::operator* (const SolidColor& c) const {
    return SolidColor(r * c.r, g * c.g, b * c.b, a * c.a);
}

SolidColor::operator/ (float f) const {
    return SolidColor(r / f, g / f, b / f, a);
}

SolidColor::operator* (float f) const {
    return SolidColor(r * f, g * f, b * f, a);
}

SolidColor::operator- () const {
    return SolidColor(-r, -g, -b, -a);
}

SolidColor::operator+ (const SolidColor& c) const {
    return SolidColor(r + c.r, g + c.g, b + c.b, a + c.a);
}

SolidColor::operator*= (float f) {
    r *= f;
    g *= f;
    b *= f;
    a *= f;
    return *this;
}

SolidColor::operator*= (const SolidColor& c) {
    r *= c.r;
    g *= c.g;
    b *= c.b;
    a *= c.a;
    return *this;
}

SolidColor::operator-= (const SolidColor& c) {
    r -= c.r;
    g -= c.g;
    b -= c.b;
    a -= c.a;
    return *this;
}

SolidColor::operator+= (const SolidColor& c) {
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
    return *this;
}

SolidColor::operator= (const SolidColor& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
    return *this;
}

SolidColor::operator+ (const SolidColor& c) const {
    return SolidColor(r + c.r, g + c.g, b + c.b, a + c.a);
}

SolidColor::operator/= (const SolidColor& c) {
    r /= c.r;
    g /= c.g;
    b /= c.b;
    a /= c.a;
    return *this;
}

SolidColor::operator/= (float f) {
    r /= f;
    g /= f;
    b /= f;
    a /= f;
    return *this;
}

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