#pragma once
#include "raygame/core/types.h"
#include <format>

namespace core {

struct Pixel {
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;

    [[nodiscard]]
    explicit constexpr operator std::string() const {
        return std::format(
            "Pixel(r: {}, g: {}, b: {}, a: {})",
            m_red,
            m_green,
            m_blue,
            m_alpha
        );
    }

    [[nodiscard]]
    std::string colour() const;
    bool        operator==(const Pixel& other) const = default;
};

namespace colour {

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
        .m_alpha = 0xFF, // NOLINT(*-magic-numbers)
    };
}

static constexpr core::Pixel VOID = rgba(0x00, 0x00, 0x00, 0x00);

static constexpr core::Pixel BLACK = rgb(0x00, 0x00, 0x00);
static constexpr core::Pixel WHITE = rgb(0xFF, 0xFF, 0xFF);
static constexpr core::Pixel RED   = rgb(0xFF, 0x00, 0x00);
static constexpr core::Pixel GREEN = rgb(0x00, 0xFF, 0x00);
static constexpr core::Pixel BLUE  = rgb(0x00, 0x00, 0xFF);

} // namespace colour
} // namespace core

RAYGAME_MAKE_FORMAT_FROM_STRING(core::Pixel)
