#pragma once
#include "core/pixel.h"

namespace core::colour {

static constexpr core::Pixel
rgba(uint8_t rval, uint8_t gval, uint8_t bval, uint8_t aval) {
    return {
        .m_red   = rval,
        .m_green = gval,
        .m_blue  = bval,
        .m_alpha = aval,
    };
}

static constexpr core::Pixel rgb(uint8_t rval, uint8_t gval, uint8_t bval) {
    return {
        .m_red   = rval,
        .m_green = gval,
        .m_blue  = bval,
        .m_alpha = 0xFF,
    };
}

static constexpr Pixel VOID = rgba(0x00, 0x00, 0x00, 0x00);

static constexpr Pixel BLACK = rgb(0x00, 0x00, 0x00);
static constexpr Pixel WHITE = rgb(0xFF, 0xFF, 0xFF);
static constexpr Pixel RED   = rgb(0xFF, 0x00, 0x00);
static constexpr Pixel GREEN = rgb(0x00, 0xFF, 0x00);
static constexpr Pixel BLUE  = rgb(0x00, 0x00, 0xFF);

} // namespace core::colours
