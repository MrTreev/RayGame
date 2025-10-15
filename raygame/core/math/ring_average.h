#pragma once
#include "raygame/core/assert.h"
#include "raygame/core/concepts.h"
#include "raygame/core/math/math.h"
#include "raygame/core/types.h"
#include <algorithm>
#include <numeric>
#include <ranges>

namespace core::math {
template<concepts::Number T, size_t bufsize>
class RingAverage {
    std::array<T, bufsize> m_buf{0};
    size_t                 m_cap{0};
    size_t                 m_pos{0};
    static constexpr T     ZERO{0};
    static_assert(bufsize > 0);

public:
    constexpr void add(T val) {
        m_buf[m_pos] = val;
        m_pos        = (m_pos + 1) % bufsize;
        if (m_cap < bufsize) [[unlikely]] {
            ++m_cap;
        }
    }

    constexpr T max() const {
        RAYGAME_ASSERT(m_cap > 0);
        const std::ranges::take_view items{m_buf, math::make_signed(m_cap)};
        return *std::max_element(items.begin(), items.end());
    }

    constexpr T min() const {
        RAYGAME_ASSERT(m_cap > 0);
        const std::ranges::take_view items{m_buf, math::make_signed(m_cap)};
        return *std::min_element(items.begin(), items.end());
    }

    constexpr T average() const {
        RAYGAME_ASSERT(m_cap > 0);
        const std::ranges::take_view items{m_buf, math::make_signed(m_cap)};
        const auto                   sum{std::reduce(items.begin(), items.end(), ZERO)};
        return sum / static_cast<T>(m_cap);
    }

    constexpr void reset() { m_cap = 0; }
};
} // namespace core::math
