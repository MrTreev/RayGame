#pragma once
#include "raygame/core/concepts.h"
#include "raygame/core/types.h"
#include <algorithm>
#include <numeric>

namespace core::math {
template<concepts::Number T, size_t bufsize>
class RingAverage {
    std::array<T, bufsize> m_buf{};
    size_t                 m_cap{0};
    size_t                 m_pos{0};
    static constexpr T     ZERO{0};
    static_assert(bufsize > 0);

public:
    void add(T val) {
        m_buf[m_pos] = val;
        m_pos        = (m_pos + 1) % bufsize;
        if (m_cap < bufsize) [[unlikely]] {
            ++m_cap;
        }
    }

    const T& max() { return *std::max_element(m_buf.cbegin(), m_buf.cend()); }

    const T& min() { return *std::min_element(m_buf.cbegin(), m_buf.cend()); }

    T average() {
        const auto sum = (std::reduce(m_buf.cbegin(), m_buf.cend(), ZERO));
        return sum / static_cast<T>(m_cap);
    }
};
} // namespace core::math
