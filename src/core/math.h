#pragma once
#include "core/debug.h"
#include "core/exception.h"
#include "core/types.h"
#include <cassert>
#include <concepts>
#include <iostream>
#include <limits>
#include <utility>

namespace core::math {

enum class MathRule {
    STRICT,
    ALLOW,
    CLAMP,
};

static constexpr MathRule MR_Default = MathRule::STRICT;

namespace constants {
constexpr float pi      = 3.14159265358979323846F;
constexpr float deg2rad = (pi / 180.0F);
constexpr float rad2deg = (180.0F / pi);
constexpr float epsilon = 0.000001F;
} // namespace constants

//! Convert Degrees to Radians
inline constexpr core::rad_t deg2rad(core::deg_t deg) {
    return deg * constants::deg2rad;
};

//! Convert Radians to Degrees
inline constexpr core::deg_t rad2deg(core::rad_t rad) {
    return rad * constants::rad2deg;
};

//! Cast one numeric type to another ensuring no change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, typename In_T, MathRule MR = MR_Default>
requires(std::integral<Out_T> && std::integral<In_T>)
inline constexpr Out_T numeric_cast(In_T input) {
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    if constexpr (MR == MathRule::STRICT) {
        if (std::in_range<Out_T>(input)) {
            return static_cast<Out_T>(input);
        } else {
            throw core::exception::Condition(std::format(
                "Input of type '{}' is above the max for output type '{}'",
                core::debug::type_name(input),
                input
            ));
        }
    }
    if constexpr (MR == MathRule::CLAMP) {
        if (std::cmp_less(input, outmin)) {
            return outmin;
        }
        if (std::cmp_greater(input, outmax)) {
            return outmax;
        }
    }
    return static_cast<Out_T>(input);
}

} // namespace core::math

std::ostream& operator<<(std::ostream& os, core::math::MathRule c);
