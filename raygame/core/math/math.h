#pragma once
#include "raygame/core/math/mathrule.h"     // IWYU pragma: export
#include "raygame/core/math/numeric_cast.h" // IWYU pragma: export
#include "raygame/core/types.h"             // IWYU pragma: export
#include <limits>
#include <numbers>
#include <type_traits>
#include <utility>

namespace core::math {
namespace constants {
constexpr float PI      = std::numbers::pi_v<float>; // NOLINT(*-identifier-length)
constexpr float DEG2RAD = (PI / 180.0F);
constexpr float RAD2DEG = (180.0F / PI);
constexpr float EPSILON = 0.000001F;
} // namespace constants

//! Convert Degrees to Radians
constexpr core::rad_t deg2rad(core::deg_t deg) {
    return deg * constants::DEG2RAD;
};

//! Convert Radians to Degrees
constexpr core::deg_t rad2deg(core::rad_t rad) {
    return rad * constants::RAD2DEG;
};

//! Convert unsigned type to signed type
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<MathRule MR = core::math::MR_DEFAULT>
constexpr auto make_signed(std::integral auto number) {
    static_assert(std::is_unsigned<decltype(number)>());
    return numeric_cast<std::make_signed_t<decltype(number)>, MR>(number);
}

//! Get the next fixed-width integer type up in size
consteval auto larger_type(std::integral auto inval) {
    if constexpr (std::is_same<decltype(inval), uint8_t>()) {
        return uint16_t{};
    } else if constexpr (std::is_same<decltype(inval), uint16_t>()) {
        return uint32_t{};
    } else if constexpr (std::is_same<decltype(inval), uint32_t>()) {
        return uint64_t{};
    } else if constexpr (std::is_same<decltype(inval), uint64_t>()) {
        return uintmax_t{};
    } else if constexpr (std::is_same<decltype(inval), int8_t>()) {
        return int16_t{};
    } else if constexpr (std::is_same<decltype(inval), int16_t>()) {
        return int32_t{};
    } else if constexpr (std::is_same<decltype(inval), int32_t>()) {
        return int64_t{};
    } else if constexpr (std::is_same<decltype(inval), int64_t>()) {
        return intmax_t{};
    } else {
        static_assert(false, "Invalid type");
    }
}

//! Get the next fixed-width integer type up in size
consteval auto smaller_type(std::integral auto inval) {
    if constexpr (std::is_same<decltype(inval), uint8_t>()) {
        static_assert(false, "No integral type smaller than uint8_t");
    } else if constexpr (std::is_same<decltype(inval), uint16_t>()) {
        return uint8_t{};
    } else if constexpr (std::is_same<decltype(inval), uint32_t>()) {
        return uint16_t{};
    } else if constexpr (std::is_same<decltype(inval), uint64_t>()) {
        return uint32_t{};
    } else if constexpr (std::is_same<decltype(inval), int8_t>()) {
        static_assert(false, "No integral type smaller than int8_t");
    } else if constexpr (std::is_same<decltype(inval), int16_t>()) {
        return int8_t{};
    } else if constexpr (std::is_same<decltype(inval), int32_t>()) {
        return int16_t{};
    } else if constexpr (std::is_same<decltype(inval), int64_t>()) {
        return int32_t{};
    } else {
        static_assert(false, "Invalid type");
    }
}

//! Get a type that can fit both @a a and @a b
consteval auto work_type(std::integral auto aval, std::integral auto bval) {
    using a_t = decltype(aval);
    using b_t = decltype(bval);
    if constexpr (std::is_same<a_t, b_t>()) {
        return a_t{};
    } else if constexpr (std::is_signed<a_t>() == std::is_signed<b_t>()) {
        if constexpr (std::numeric_limits<a_t>::max() > std::numeric_limits<b_t>::max()) {
            return a_t{};
        } else {
            return b_t{};
        }
    } else {
        if constexpr (std::is_signed<a_t>()) {
            if constexpr (sizeof(a_t) <= sizeof(b_t)) {
                using ret_t = std::make_signed_t<decltype(larger_type(bval))>;
                return ret_t{};
            } else {
                return a_t{};
            }
        } else {
            if constexpr (sizeof(b_t) <= sizeof(a_t)) {
                using ret_t = std::make_signed_t<decltype(larger_type(aval))>;
                return ret_t{};
            } else {
                return b_t{};
            }
        }
    }
}

//! Absolute value function
constexpr auto abs(std::integral auto aval) -> decltype(aval) {
    if constexpr (std::cmp_less(aval, 0)) {
        return -aval;
    }
    return aval;
}
} // namespace core::math
