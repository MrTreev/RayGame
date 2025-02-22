#pragma once
#include "raygame/core/types.h"
#include <format>
#include <sstream>

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
};

} // namespace core

RAYGAME_MAKE_FORMAT_FROM_STRING(core::Pixel)
