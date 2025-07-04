#pragma once
#include "raygame/core/debug.h"
#include "raygame/core/exception.h"
#include "raygame/core/math/mathrule.h"
#include <concepts>
#include <format>
#include <utility>

namespace core::math {

//! Cast one numeric type to another ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
requires(std::integral<Out_T>)
constexpr Out_T numeric_cast(auto input) {
    static_assert(std::is_integral<decltype(input)>());
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    if constexpr (MR == MathRule::STRICT) {
        if (std::in_range<Out_T>(input)) {
            return static_cast<Out_T>(input);
        }
        throw core::exception::Condition(
            std::format(
                "Input of type '{}' is outside the range for output type '{}'",
                core::debug::type_name(input),
                input
            )
        );
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
