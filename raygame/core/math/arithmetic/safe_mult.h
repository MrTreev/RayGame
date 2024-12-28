#pragma once
#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/debug.h"
#include "raygame/core/exception.h"
#include "raygame/core/math/numeric_cast.h"
#include <concepts>
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

//! Multiply two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<std::integral Out_T, MathRule MR = core::math::MR_DEFAULT>
constexpr Out_T
// NOLINTNEXTLINE(*-cognitive-complexity)
safe_mult(const std::integral auto aval, const std::integral auto bval) {
    using core::debug::type_name;
    using core::exception::Condition;
    using core::math::numeric_cast;
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin [[maybe_unused]]
    = std::numeric_limits<Out_T>::lowest();

    if (aval == 0 || bval == 0) {
        return 0;
    }

    if constexpr (core::config::COMPILER_IS_GCC_LIKE
                  && !core::config::FORCE_GENERIC_IMPL) {
        Out_T res = 0;
        if ((!__builtin_mul_overflow(aval, bval, &res))
            || (MR == MathRule::ALLOW)) {
            return res;
        }
        if constexpr (MR == MathRule::STRICT) {
            throw Condition(std::format(
                "Result of multiplication ({} * {}) is outside the range of "
                "output type '{}'",
                aval,
                bval,
                type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmax;
        } else {
            condition::unknown("");
        }
    } else {
        if (std::cmp_greater(bval, outmax / aval)
            || (std::cmp_less_equal(aval, -1)
                && std::cmp_less_equal(bval, outmin))
            || (std::cmp_less_equal(bval, -1)
                && std::cmp_less_equal(aval, outmin))) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of multiplication ({} * {}) is above the max for "
                    "output type '{}'",
                    aval,
                    bval,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmax;
            }
        } else if (std::is_unsigned<Out_T>()
                   && (std::cmp_less(aval, 0) || std::cmp_less(bval, 0))) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of multiplication ({} * {}) is below the min for "
                    "output type '{}'",
                    aval,
                    bval,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmin;
            }
        }
        return numeric_cast<Out_T, MR>(aval * bval);
    }
}

} // namespace core::math
