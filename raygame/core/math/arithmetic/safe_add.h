#pragma once
#include "raygame/core/base/condition.h"
#include "raygame/core/base/config.h"
#include "raygame/core/base/debug.h"
#include "raygame/core/base/exception.h"
#include "raygame/core/math/math.h"
#include "raygame/core/math/numeric_cast.h"
#include <concepts>
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

//! Add two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
requires(std::integral<Out_T>)
constexpr Out_T safe_add(const auto a, const auto b) {
    static_assert(
        std::is_integral<Out_T>() && std::is_integral<decltype(a)>()
        && std::is_integral<decltype(b)>()
    );
    using core::debug::type_name;
    using core::exception::Condition;
    using core::math::numeric_cast;
    constexpr Out_T outmax   = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin   = std::numeric_limits<Out_T>::lowest();
    using work_t             = decltype(work_type(work_type(a, b), Out_T{0}));
    constexpr work_t workmin = static_cast<work_t>(outmin);
    constexpr work_t workmax = static_cast<work_t>(outmax);

    const work_t worka = static_cast<work_t>(a);
    const work_t workb = static_cast<work_t>(b);

    if constexpr (core::config::COMPILER_IS_GCC_LIKE
                  && !core::config::FORCE_GENERIC_IMPL) {
        Out_T res = 0;
        if ((!__builtin_add_overflow(a, b, &res)) || (MR == MathRule::ALLOW)) {
            return res;
        } else if constexpr (MR == MathRule::STRICT) {
            throw Condition(std::format(
                "Result of addition ({} + {}) is outside the range of "
                "output type '{}'",
                a,
                b,
                type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            if (std::cmp_greater(b, workmax - worka)
                || std::cmp_greater(a, workmax - workb)) {
                return outmax;
            } else {
                return outmin;
            }
        }
        RAYGAME_ELSE_UNKNOWN("");
    } else {
        if (std::cmp_greater(a, 0) && std::cmp_greater(b, workmax - worka)) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of addition ({} + {}) is above the max for output "
                    "type '{}'",
                    a,
                    b,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmax;
            }
        } else if (std::cmp_less(a, 0) && std::cmp_less(b, workmin - worka)) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of addition ({} + {}) is below the min for output "
                    "type '{}'",
                    a,
                    b,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmin;
            }
        }
        return numeric_cast<Out_T, MR>(worka + workb);
    }
}

} // namespace core::math
