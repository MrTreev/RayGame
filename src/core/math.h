#pragma once
#include "core/config.h"
#include "core/debug.h"
#include "core/exception.h"
#include "core/types.h"
#include "core/vector.h"
#include <cassert>
#include <concepts>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

//! Rule for dealing with out-of-range errors
enum class MathRule {
    //! Throw an exception
    STRICT,
    //! Do nothing, return whatever would be normally returned
    ALLOW,
    //! Clamp to the range representable by the desired type
    CLAMP,
};

namespace {
consteval MathRule default_mathrule() {
    if constexpr (core::config::BUILD_TYPE == core::config::BuildType::DEBUG) {
        return MathRule::STRICT;
    } else {
        return MathRule::ALLOW;
    }
}
} // namespace

//! Default MathRule, STRICT for debug, ALLOW for production
static constexpr MathRule MR_DEFAULT = default_mathrule();

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

//! Cast one numeric type to another ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
requires(std::integral<Out_T>)
inline constexpr Out_T numeric_cast(auto input) {
    static_assert(std::is_integral<decltype(input)>());
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

//! Convert unsigned type to signed type
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<MathRule MR = core::math::MR_DEFAULT>
inline constexpr auto make_signed(auto number) {
    static_assert(std::is_unsigned<decltype(number)>());
    return numeric_cast<std::make_signed_t<decltype(number)>, MR>(number);
}

//! Create a Vec2 of a and b using the larger of the two types
inline constexpr auto max_type(auto a, auto b) {
    static_assert(
        std::is_integral<decltype(a)>() && std::is_integral<decltype(b)>()
    );
    if constexpr (std::is_unsigned<decltype(a)>()
                  == std::is_unsigned<decltype(b)>()) {
        if constexpr (std::cmp_greater(
                          std::numeric_limits<decltype(a)>::max(),
                          std::numeric_limits<decltype(b)>::max()
                      )) {
            return core::Vec2(a, static_cast<decltype(a)>(b));
        } else {
            return core::Vec2(static_cast<decltype(b)>(a), b);
        }
    } else {
        if constexpr (std::cmp_equal(
                          std::numeric_limits<decltype(a)>::max(),
                          std::numeric_limits<decltype(b)>::max()
                      )) {
            if constexpr (std::is_signed<decltype(a)>()) {
                return core::Vec2(a, static_cast<decltype(a)>(b));
            } else {
                return core::Vec2(static_cast<decltype(b)>(a), b);
            }
        }
        if constexpr (std::cmp_greater(
                          std::numeric_limits<decltype(a)>::max(),
                          std::numeric_limits<decltype(b)>::max()
                      )) {
            return core::Vec2(a, static_cast<decltype(a)>(b));
        } else {
            return core::Vec2(static_cast<decltype(b)>(a), b);
        }
    }
}

} // namespace core::math

std::ostream& operator<<(std::ostream& os, core::math::MathRule c);
