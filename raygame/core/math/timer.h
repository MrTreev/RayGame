#pragma once
#include <chrono>

namespace core::math {
template<
    typename Clock_T    = std::chrono::high_resolution_clock,
    typename Duration_T = typename Clock_T::duration>
class Timer {
    using clock_t     = Clock_T;
    using duration_t  = Duration_T;
    using timepoint_t = std::chrono::time_point<clock_t, duration_t>;

    timepoint_t m_begin{};
    timepoint_t m_end{};

public:
    void start() { m_begin = clock_t::now(); }

    void end() { m_end = clock_t::now(); }

    duration_t delta() { return std::chrono::duration_cast<duration_t>(m_end - m_begin); }

    std::chrono::milliseconds ms() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_begin);
    }

    std::chrono::seconds sec() {
        return std::chrono::duration_cast<std::chrono::seconds>(m_end - m_begin);
    }
};

using HighResolutionTimer =
    Timer<std::chrono::high_resolution_clock, std::chrono::high_resolution_clock::duration>;

extern template class Timer<
    std::chrono::high_resolution_clock,
    std::chrono::high_resolution_clock::duration>;
} // namespace core::math
