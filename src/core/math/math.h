#pragma once
#include "core/base/config.h"
#include "core/base/types.h"
#include "core/math/vector.h"
#include <cassert>
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
