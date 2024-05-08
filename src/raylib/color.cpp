#include "raylib/color.h"
#include <format>

void raylib::Color::set(const ::Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

raylib::Color::Color(::Vector4 normalized) {
    set(::ColorFromNormalized(normalized));
}

raylib::Color::Color(const ::Color& color)
    : ::Color{color.r, color.g, color.b, color.a} {}

raylib::Color::Color(
    unsigned char red,
    unsigned char green,
    unsigned char blue,
    unsigned char alpha
)
    : ::Color{red, green, blue, alpha} {};

raylib::Color::Color()
    : ::Color{0, 0, 0, 255} {};

raylib::Color::Color(::Vector3 hsv) {
    set(::ColorFromHSV(hsv.x, hsv.y, hsv.z));
}

raylib::Color::Color(unsigned int hexValue) {
    set(::GetColor(hexValue));
}

raylib::Color::Color(void* srcPtr, int format) {
    set(::GetPixelColor(srcPtr, format));
}

::Color raylib::Color::FromHSV(float hue, float saturation, float value) {
    return ::ColorFromHSV(hue, saturation, value);
}

int raylib::Color::ToInt() const {
    return ::ColorToInt(*this);
}

std::string raylib::Color::ToString() const {
    return std::format("Color({}, {}, {}, {})", r, g, b, a);
}

raylib::Color raylib::Color::Fade(float alpha) const {
    return ::Fade(*this, alpha);
}

raylib::Vector4 raylib::Color::Normalize() const {
    return ::ColorNormalize(*this);
}

Vector3 raylib::Color::ToHSV() const {
    return ::ColorToHSV(*this);
}

raylib::Color raylib::Color::Tint(::Color tint) {
    return ::ColorTint(*this, tint);
}

raylib::Color raylib::Color::Brightness(float factor) {
    return ::ColorBrightness(*this, factor);
}

raylib::Color raylib::Color::Contrast(float contrast) {
    return ::ColorContrast(*this, contrast);
}

raylib::Color raylib::Color::Alpha(float alpha) const {
    return ::ColorAlpha(*this, alpha);
}

raylib::Color raylib::Color::AlphaBlend(::Color dst, ::Color tint) const {
    return ::ColorAlphaBlend(dst, *this, tint);
}

unsigned char raylib::Color::GetR() const {
    return r;
}

void raylib::Color::SetR(unsigned char value) {
    r = value;
}

unsigned char raylib::Color::GetG() const {
    return g;
}

void raylib::Color::SetG(unsigned char value) {
    g = value;
}

unsigned char raylib::Color::GetB() const {
    return b;
}

void raylib::Color::SetB(unsigned char value) {
    b = value;
}

unsigned char raylib::Color::GetA() const {
    return a;
}

void raylib::Color::SetA(unsigned char value) {
    a = value;
}
