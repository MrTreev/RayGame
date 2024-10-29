#pragma once
#include "core/base/condition.h"
#include "core/base/config.h"
#include "core/base/debug.h"
#include "core/base/exception.h"
#include "core/math/numeric_cast.h"
#include <concepts>
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

//! Multiply two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
requires(std::integral<Out_T>)
inline constexpr Out_T safe_mult(const auto a, const auto b) {
    static_assert(
        std::is_integral<Out_T>() && std::is_integral<decltype(a)>()
        && std::is_integral<decltype(b)>()
    );
    using core::debug::type_name;
    using core::exception::Condition;
    using core::math::numeric_cast;
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin [[maybe_unused]]
    = std::numeric_limits<Out_T>::lowest();

    if (a == 0 || b == 0) {
        return 0;
    }

    if constexpr (core::config::COMPILER_IS_GCC_LIKE
                  && !core::config::FORCE_GENERIC_IMPL) {
        Out_T res = 0;
        if ((!__builtin_mul_overflow(a, b, &res)) || (MR == MathRule::ALLOW)) {
            return res;
        } else if constexpr (MR == MathRule::STRICT) {
            throw Condition(std::format(
                "Result of multiplication ({} * {}) is outside the range of "
                "output type '{}'",
                a,
                b,
                type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmax;
        }
        RAYGAME_ELSE_UNKNOWN("");
    } else {
        if (std::cmp_greater(b, outmax / a)
            || (std::cmp_less_equal(a, -1) && std::cmp_less_equal(b, outmin))
            || (std::cmp_less_equal(b, -1) && std::cmp_less_equal(a, outmin))) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of multiplication ({} * {}) is above the max for "
                    "output type '{}'",
                    a,
                    b,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmax;
            }
        } else if (std::is_unsigned<Out_T>()
                   && (std::cmp_less(a, 0) || std::cmp_less(b, 0))) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of multiplication ({} * {}) is below the min for "
                    "output type '{}'",
                    a,
                    b,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmin;
            }
        }
        return numeric_cast<Out_T, MR>(a * b);
    }
}

} // namespace core::math
