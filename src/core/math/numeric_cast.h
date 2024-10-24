#pragma once
#include "core/base/debug.h"
#include "core/base/exception.h"
#include "core/math/math.h"
#include <concepts>
#include <format>

namespace core::math {

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

} // namespace core::math
