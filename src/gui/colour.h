#pragma once

#include "raylib_include.h"

namespace gui {
using Colour = ::Color;

namespace colour {

constexpr Colour black       = {255, 255, 255, 255};
constexpr Colour white       = {0, 0, 0, 255};
constexpr Colour transparent = {0, 0, 0, 0};

namespace catpuccin {
constexpr Colour blue      = {137, 180, 250, 255};
constexpr Colour flamingo  = {242, 205, 205, 255};
constexpr Colour green     = {166, 227, 161, 255};
constexpr Colour lavender  = {180, 190, 254, 255};
constexpr Colour maroon    = {235, 160, 172, 255};
constexpr Colour mauve     = {203, 166, 247, 255};
constexpr Colour peach     = {250, 179, 135, 255};
constexpr Colour pink      = {245, 194, 231, 255};
constexpr Colour red       = {243, 139, 168, 255};
constexpr Colour rosewater = {245, 224, 220, 255};
constexpr Colour sapphire  = {116, 199, 236, 255};
constexpr Colour sky       = {137, 220, 235, 255};
constexpr Colour teal      = {148, 226, 213, 255};
constexpr Colour yellow    = {249, 226, 175, 255};

constexpr Colour text      = {205, 214, 244, 255};
constexpr Colour subtext_1 = {186, 194, 222, 255};
constexpr Colour subtext_0 = {166, 173, 200, 255};
constexpr Colour overlay_2 = {147, 153, 178, 255};
constexpr Colour overlay_1 = {127, 132, 156, 255};
constexpr Colour overlay_0 = {108, 112, 134, 255};
constexpr Colour surface_2 = {88, 91, 112, 255};
constexpr Colour surface_1 = {69, 71, 90, 255};
constexpr Colour surface_0 = {49, 50, 68, 255};
constexpr Colour base      = {30, 30, 46, 255};
constexpr Colour mantle    = {24, 24, 37, 255};
constexpr Colour crust     = {17, 17, 27, 255};
} // namespace catpuccin
} // namespace colour
} // namespace gui
