#pragma once
#include "core/exception.h"
#include "core/math.h"
#include <concepts>

namespace core::math {

//! Add two numeric types ensuring no overflows or underflows
template<
    typename Out_T,
    typename A_T,
    typename B_T,
    MathRule MR = core::math::MR_Default>
requires(std::integral<Out_T> && std::integral<A_T> && std::integral<B_T>)
inline constexpr Out_T safe_add(A_T a, B_T b) {
    constexpr A_T   a_max  = std::numeric_limits<A_T>::max();
    constexpr A_T   a_min  = std::numeric_limits<A_T>::lowest();
    constexpr B_T   b_max  = std::numeric_limits<B_T>::max();
    constexpr B_T   b_min  = std::numeric_limits<B_T>::lowest();
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    if constexpr (MR == MathRule::STRICT) {
        throw core::exception::Condition(std::format(
            "Result of addition ({} + {}) is above the max for output type "
            "'{}'",
            a,
            b,
            core::debug::type_name<Out_T>()
        ));
    }
    if constexpr (MR == MathRule::CLAMP) {}
}

} // namespace core::math
