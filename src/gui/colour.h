#pragma once
#include "gui/raylib_include.h"
#include <cstdint>

namespace gui {
class Colour {
private:
    ::Color _colour;

public:
    Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
        : _colour(red, green, blue, alpha) {}

    [[nodiscard]]
    ::Color col() const {
        return _colour;
    }

    [[nodiscard]]
    uint8_t red() const {
        return _colour.r;
    }

    [[nodiscard]]
    uint8_t green() const {
        return _colour.g;
    }

    [[nodiscard]]
    uint8_t blue() const {
        return _colour.b;
    }

    [[nodiscard]]
    uint8_t alpha() const {
        return _colour.a;
    }
};

namespace colour {

extern const Colour black;
extern const Colour white;
extern const Colour transparent;

namespace catpuccin {
extern const Colour blue;
extern const Colour flamingo;
extern const Colour green;
extern const Colour lavender;
extern const Colour maroon;
extern const Colour mauve;
extern const Colour peach;
extern const Colour pink;
extern const Colour red;
extern const Colour rosewater;
extern const Colour sapphire;
extern const Colour sky;
extern const Colour teal;
extern const Colour yellow;

extern const Colour text;
extern const Colour subtext_1;
extern const Colour subtext_0;
extern const Colour overlay_2;
extern const Colour overlay_1;
extern const Colour overlay_0;
extern const Colour surface_2;
extern const Colour surface_1;
extern const Colour surface_0;
extern const Colour base;
extern const Colour mantle;
extern const Colour crust;
} // namespace catpuccin
} // namespace colour
} // namespace gui
