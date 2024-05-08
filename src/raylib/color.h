#pragma once

#include "raylib/raylib.h"
#include "raylib/vector4.h"
#include <string>

namespace raylib {
class Color: public ::Color {
public:
    Color(const ::Color& color); //NOLINT hicpp-explicit-conversions

    Color(
        unsigned char red,
        unsigned char green,
        unsigned char blue,
        unsigned char alpha = 255
    );

    Color();
    explicit Color(::Vector3 hsv);
    explicit Color(::Vector4 normalized);
    explicit Color(unsigned int hexValue);
    Color(void* srcPtr, int format);

    Color   Brightness(float factor);
    Color   Fade(float alpha) const;
    Color   Tint(::Color tint);
    Color   Alpha(float alpha) const;
    Color   AlphaBlend(::Color dst, ::Color tint) const;
    Color   Contrast(float contrast);
    Vector3 ToHSV() const;
    Vector4 Normalize() const;

    int         ToInt() const;
    std::string ToString() const;

    explicit operator int() const {
        return ToInt();
    };

    explicit operator std::string() const {
        return ToString();
    };

    static ::Color FromHSV(float hue, float saturation, float value);

    unsigned char GetA() const;
    unsigned char GetB() const;
    unsigned char GetG() const;
    unsigned char GetR() const;
    void          SetA(unsigned char value);
    void          SetB(unsigned char value);
    void          SetG(unsigned char value);
    void          SetR(unsigned char value);

protected:
    void set(const ::Color& color);
};

} // namespace raylib
