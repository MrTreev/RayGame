#pragma once
#include "raygame/core/types.h"
#include <format>

namespace core {

struct Pixel {
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;
};

[[nodiscard]]
constexpr std::string tostring(const Pixel& pixel) {
    return std::format(
        "Pixel(r: {}, g: {}, b: {}, a: {})",
        pixel.m_red,
        pixel.m_green,
        pixel.m_blue,
        pixel.m_alpha
    );
}
} // namespace core
