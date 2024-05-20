#include "core/raycpp/color.h"
#include <format>

void core::raycpp::Color::set(const ::Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

core::raycpp::Color::Color(::Vector4 normalized) {
    set(::ColorFromNormalized(normalized));
}

core::raycpp::Color::Color(const ::Color& color)
    : ::Color{color.r, color.g, color.b, color.a} {}

core::raycpp::Color::Color(
    unsigned char red,
    unsigned char green,
    unsigned char blue,
    unsigned char alpha
)
    : ::Color{red, green, blue, alpha} {};

core::raycpp::Color::Color()
    : ::Color{0, 0, 0, 255} {};

core::raycpp::Color::Color(::Vector3 hsv) {
    set(::ColorFromHSV(hsv.x, hsv.y, hsv.z));
}

core::raycpp::Color::Color(unsigned int hexValue) {
    set(::GetColor(hexValue));
}

core::raycpp::Color::Color(void* srcPtr, int format) {
    set(::GetPixelColor(srcPtr, format));
}

::Color core::raycpp::Color::FromHSV(float hue, float saturation, float value) {
    return ::ColorFromHSV(hue, saturation, value);
}

int core::raycpp::Color::ToInt() const {
    return ::ColorToInt(*this);
}

std::string core::raycpp::Color::ToString() const {
    return std::format("Color({}, {}, {}, {})", r, g, b, a);
}

core::raycpp::Color core::raycpp::Color::Fade(float alpha) const {
    return Color(::Fade(*this, alpha));
}

core::raycpp::Vector4 core::raycpp::Color::Normalize() const {
    return core::raycpp::Vector4(::ColorNormalize(*this));
}

Vector3 core::raycpp::Color::ToHSV() const {
    return ::ColorToHSV(*this);
}

core::raycpp::Color core::raycpp::Color::Tint(::Color tint) {
    return Color(::ColorTint(*this, tint));
}

core::raycpp::Color core::raycpp::Color::Brightness(float factor) {
    return Color(::ColorBrightness(*this, factor));
}

core::raycpp::Color core::raycpp::Color::Contrast(float contrast) {
    return Color(::ColorContrast(*this, contrast));
}

core::raycpp::Color core::raycpp::Color::Alpha(float alpha) const {
    return Color(::ColorAlpha(*this, alpha));
}

core::raycpp::Color core::raycpp::Color::AlphaBlend(::Color dst, ::Color tint) const {
    return Color(::ColorAlphaBlend(dst, *this, tint));
}

unsigned char core::raycpp::Color::GetR() const {
    return r;
}

void core::raycpp::Color::SetR(unsigned char value) {
    r = value;
}

unsigned char core::raycpp::Color::GetG() const {
    return g;
}

void core::raycpp::Color::SetG(unsigned char value) {
    g = value;
}

unsigned char core::raycpp::Color::GetB() const {
    return b;
}

void core::raycpp::Color::SetB(unsigned char value) {
    b = value;
}

unsigned char core::raycpp::Color::GetA() const {
    return a;
}

void core::raycpp::Color::SetA(unsigned char value) {
    a = value;
}
