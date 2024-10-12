#pragma once
#include "core/debug.h"
#include "core/exception.h"
#include "core/types.h"
#include <cassert>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

enum class MathRule {
    STRICT,
    ALLOW,
    CLAMP,
};

static constexpr MathRule MR_DEFAULT = MathRule::STRICT;

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

template<typename T>
struct type_holder {
    using type = T;
};

inline constexpr auto make_signed(const auto& number) {
    static_assert(std::is_signed_v<decltype(number)> || std::is_unsigned_v<decltype(number)>);
    if constexpr (std::is_unsigned_v<decltype(number)>) {
        if constexpr (std::is_same_v<decltype(number), uint8_t>) {
            return static_cast<int16_t>(number);
        }
        if constexpr (std::is_same_v<decltype(number), uint16_t>) {
            return static_cast<int32_t>(number);
        }
        if constexpr (std::is_same_v<decltype(number), uint32_t>) {
            return static_cast<int64_t>(number);
        }
        if constexpr (std::is_same_v<decltype(number), uint64_t>) {
            return static_cast<std::intmax_t>(number);
        }
    } else if constexpr (std::is_signed_v<decltype(number)>) {
        return number;
    }
}

inline constexpr auto max_type(auto a, auto b) {
    static_assert(std::is_integral_v<decltype(a)> && std::is_integral_v<decltype(b)>);
    if constexpr (std::is_unsigned_v<decltype(a)>
                  == std::is_unsigned_v<decltype(b)>) {
        if constexpr (std::cmp_greater(
                          std::numeric_limits<decltype(a)>::max(),
                          std::numeric_limits<decltype(b)>::max()
                      )) {
            return a;
        } else {
            return b;
        }
    } else {
        if constexpr (std::cmp_equal(
                          std::numeric_limits<decltype(a)>::max(),
                          std::numeric_limits<decltype(b)>::max()
                      )) {
            if constexpr (std::is_signed_v<decltype(a)>) {
                return a;
            } else {
                return b;
            }
        }
        if constexpr (std::cmp_greater(
                          std::numeric_limits<decltype(a)>::max(),
                          std::numeric_limits<decltype(b)>::max()
                      )) {
            return make_signed(a);
        } else {
            return make_signed(b);
        }
    }
}

//! Cast one numeric type to another ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
requires(std::integral<Out_T>)
inline constexpr Out_T numeric_cast(auto input) {
    static_assert(std::is_integral_v<decltype(input)>);
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
    } else if constexpr (MR == MathRule::CLAMP) {
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
