#pragma once
#include "core/drawing/pixel.h"

namespace core::colour {

static constexpr core::Pixel
rgba(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    return {
        .m_red   = red,
        .m_green = green,
        .m_blue  = blue,
        .m_alpha = alpha,
    };
}

static constexpr core::Pixel rgb(uint8_t red, uint8_t green, uint8_t blue) {
    return {
        .m_red   = red,
        .m_green = green,
        .m_blue  = blue,
        .m_alpha = 0xFF,
    };
}

static constexpr Pixel VOID = rgba(0x00, 0x00, 0x00, 0x00);

static constexpr Pixel BLACK = rgb(0x00, 0x00, 0x00);
static constexpr Pixel WHITE = rgb(0xFF, 0xFF, 0xFF);
static constexpr Pixel RED   = rgb(0xFF, 0x00, 0x00);
static constexpr Pixel GREEN = rgb(0x00, 0xFF, 0x00);
static constexpr Pixel BLUE  = rgb(0x00, 0x00, 0xFF);

} // namespace core::colour
