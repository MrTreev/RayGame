#pragma once
#include "core/base/condition.h"
#include "core/base/config.h"
#include "core/base/debug.h"
#include "core/base/exception.h"
#include "core/math/math.h"
#include "core/math/numeric_cast.h"
#include <concepts>
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

//! Subtract two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
requires(std::integral<Out_T>)
inline constexpr Out_T safe_sub(const auto a, const auto b) {
    static_assert(
        std::is_integral<Out_T>() && std::is_integral<decltype(a)>()
        && std::is_integral<decltype(b)>()
    );
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    using core::debug::type_name;
    using core::exception::Condition;
    using core::math::numeric_cast;

    if constexpr (core::config::COMPILER_IS_GCC_LIKE
                  && !core::config::FORCE_GENERIC_IMPL) {
        Out_T res = 0;
        if ((!__builtin_sub_overflow(a, b, &res)) || (MR == MathRule::ALLOW)) {
            return res;
        } else if constexpr (MR == MathRule::STRICT) {
            throw Condition(std::format(
                "Result of subtraction ({} - {}) is outside the range of "
                "output type '{}'",
                a,
                b,
                type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            if (std::cmp_greater(b, outmin + a)
                || std::cmp_greater(a, outmin + b)) {
                return outmin;
            } else {
                return outmax;
            }
        }
        RAYGAME_ELSE_UNKNOWN("");
    } else {
        if (std::cmp_less(a, 0) && std::cmp_greater(b, (+outmax) + (+a))) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of subtraction ({} - {}) is above the max for "
                    "output "
                    "type '{}'",
                    a,
                    b,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmax;
            }
        } else if (std::cmp_greater(a, 0)
                   && std::cmp_less(b, ((+outmin) + (+a)))) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of subtraction ({} - {}) is below the min for "
                    "output type '{}'",
                    a,
                    b,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmin;
            }
        }
        return numeric_cast<Out_T, MR>(a - b);
    }
}

} // namespace core::math
