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
    constexpr std::string tostring() const {
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
