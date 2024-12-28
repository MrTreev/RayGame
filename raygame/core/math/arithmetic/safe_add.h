#pragma once
#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/debug.h"
#include "raygame/core/exception.h"
#include "raygame/core/math/math.h"
#include "raygame/core/math/numeric_cast.h"
#include <limits>
#include <utility>

namespace core::math {
//! Add two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<std::integral Out_T, MathRule MR = core::math::MR_DEFAULT>
constexpr Out_T
// NOLINTNEXTLINE(*-cognitive-complexity)
safe_add(const std::integral auto aval, const std::integral auto bval) {
    using work_t = decltype(work_type(work_type(aval, bval), Out_T{0}));
    if constexpr (core::config::COMPILER_IS_GCC_LIKE
                  && !core::config::FORCE_GENERIC_IMPL) {
        Out_T res = 0;
        if ((!__builtin_add_overflow(aval, bval, &res))
            || (MR == MathRule::ALLOW)) {
            return res;
        }
        if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(std::format(
                "Result of addition ({} + {}) is outside the range of "
                "output type '{}'",
                aval,
                bval,
                core::debug::type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            constexpr auto workmax =
                static_cast<work_t>(std::numeric_limits<Out_T>::max());
            if (std::cmp_greater(bval, workmax - static_cast<work_t>(aval))
                || std::cmp_greater(
                    aval,
                    workmax - static_cast<work_t>(bval)
                )) {
                return std::numeric_limits<Out_T>::max();
            }
            return std::numeric_limits<Out_T>::lowest();

        } else {
            core::condition::unknown("");
        }
    } else {
        const auto worka = static_cast<work_t>(aval);
        const auto workb = static_cast<work_t>(bval);

        if (std::cmp_greater(aval, 0)
            && std::cmp_greater(
                bval,
                static_cast<work_t>(std::numeric_limits<Out_T>::max()) - worka
            )) {
            if constexpr (MR == MathRule::STRICT) {
                throw core::exception::Condition(std::format(
                    "Result of addition ({} + {}) is above the max for output "
                    "type '{}'",
                    aval,
                    bval,
                    core::debug::type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return std::numeric_limits<Out_T>::max();
            }
        } else if (std::cmp_less(aval, 0)
                   && std::cmp_less(
                       bval,
                       static_cast<work_t>(std::numeric_limits<Out_T>::lowest())
                           - worka
                   )) {
            if constexpr (MR == MathRule::STRICT) {
                throw core::exception::Condition(std::format(
                    "Result of addition ({} + {}) is below the min for output "
                    "type '{}'",
                    aval,
                    bval,
                    core::debug::type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return std::numeric_limits<Out_T>::lowest();
            }
        }
        return core::math::numeric_cast<Out_T, MR>(worka + workb);
    }
}

} // namespace core::math
