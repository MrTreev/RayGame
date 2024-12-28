#pragma once
#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/debug.h"
#include "raygame/core/exception.h"
#include "raygame/core/math/arithmetic/safe_add.h"
#include "raygame/core/math/math.h"
#include "raygame/core/math/numeric_cast.h"
#include <concepts>
#include <cstdlib>
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

//! Subtract two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<std::integral Out_T, MathRule MR = core::math::MR_DEFAULT>
// NOLINTNEXTLINE(*-cognitive-complexity)
Out_T safe_sub(const std::integral auto aval, const std::integral auto bval) {
    using work_t = decltype(work_type(work_type(aval, bval), Out_T{0}));
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();

    if constexpr (core::config::COMPILER_IS_GCC_LIKE
                  && !core::config::FORCE_GENERIC_IMPL) {
        Out_T res = 0;
        if (__builtin_sub_overflow(aval, bval, &res)) {
            if constexpr (MR == MathRule::ALLOW) {
                return core::math::numeric_cast<Out_T, MR>(res);
            }
            if constexpr (MR == MathRule::STRICT) {
                throw core::exception::Condition(std ::format(
                    "Result of subtraction ({} - {}) is outside the range of "
                    "output type '{}'",
                    aval,
                    bval,
                    core ::debug ::type_name<Out_T>()
                ));
            }
            if constexpr (MR == MathRule::CLAMP) {
                if (std::cmp_greater(
                        static_cast<work_t>(bval),
                        static_cast<work_t>(outmin) + static_cast<work_t>(aval)
                    )) {
                    return outmin;
                }
                return std::numeric_limits<Out_T>::max();
            }
            condition::unreachable();
        } else {
            return core::math::numeric_cast<Out_T, MR>(res);
        }
    } else {
        const auto worka = static_cast<work_t>(aval);
        const auto workb = static_cast<work_t>(bval);
        if constexpr (MR == MathRule::ALLOW) {
            return core::math::numeric_cast<Out_T, MR>(worka - workb);
        }
        if (std::cmp_equal(bval, aval)) {
            return 0;
        }
        if (std::cmp_equal(aval, 0)) {
            return core::math::numeric_cast<Out_T, MR>(-bval);
        }
        if (std::cmp_equal(bval, 0)) {
            return core::math::numeric_cast<Out_T, MR>(aval);
        }
        if (std::is_unsigned<work_t>()) {
            if (aval >= bval) {
                return numeric_cast<Out_T, MR>(worka - workb);
            }
            if constexpr (MR == MathRule::STRICT) {
                throw core::exception::Condition(std ::format(
                    "Result of subtraction ({} - {}) is outside the range of "
                    "output type '{}'",
                    aval,
                    bval,
                    core ::debug ::type_name<Out_T>()
                ));
            }
            if (MR == MathRule::CLAMP) {
                return outmin;
            }
        }
        return safe_add<Out_T, MR>(worka, -workb);
    }
    condition::unreachable();
}

} // namespace core::math
