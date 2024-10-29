#pragma once
#include "core/base/types.h"
#include "core/math/mathrule.h"
#include <cassert>
#include <limits>
#include <type_traits>

namespace core::math {
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

inline consteval auto work_type(const auto a, const auto b) {
    using a_t = decltype(a);
    using b_t = decltype(b);
    if constexpr (std::is_same<a_t, b_t>()) {
        return a_t{};
    }
    if constexpr (std::is_signed<a_t>() == std::is_signed<b_t>()) {
        if constexpr (std::numeric_limits<a_t>::max()
                      > std::numeric_limits<b_t>::max()) {
            return a_t{};
        } else {
            return b_t{};
        }
    } else {
        if constexpr (std::is_signed<a_t>()) {
            if constexpr (sizeof(a_t) <= sizeof(b_t)) {
                using ret_t = std::make_signed<decltype(+b)>::type;
                return ret_t{};
            } else {
                return a_t{};
            }
        } else {
            if constexpr (sizeof(b_t) <= sizeof(a_t)) {
                using ret_t = std::make_signed<decltype(+a)>::type;
                return ret_t{};
            } else {
                return b_t{};
            }
        }
    }
}

} // namespace core::math
