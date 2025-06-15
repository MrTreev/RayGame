#pragma once
#include "raygame/core/config.h"
#include "raygame/core/types.h"
#include <numeric>

namespace core::math {
template<typename T, size_t bufsize>
class RingAverage {
    std::array<T, bufsize> m_buf{};
    size_t                 m_cap{0};
    size_t                 m_pos{0};
    static constexpr T     ZERO{0};

public:
    void add(T val) {
        m_buf[m_pos] = val;
        m_pos        = (m_pos + 1) % bufsize;
        if (m_cap < bufsize) [[unlikely]] {
            ++m_cap;
        }
    }

    T average() {
        return (std::reduce(m_buf.cbegin(), m_buf.cend(), ZERO)) / static_cast<T>(m_cap);
    }
};
extern template class RingAverage<size_t, core::config::TARGET_FPS>;
} // namespace core::math
