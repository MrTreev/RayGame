#pragma once
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

#define RG_OOR_STRING                                                          \
    std::format(                                                               \
        "Result of subtraction ({} - {}) is outside the range of "             \
        "output type '{}'",                                                    \
        a,                                                                     \
        b,                                                                     \
        core::debug::type_name<Out_T>()                                        \
    )

//! Subtract two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
requires(std::integral<Out_T>)
Out_T safe_sub(const auto a, const auto b) {
    static_assert(
        std::is_integral<Out_T>() && std::is_integral<decltype(a)>()
        && std::is_integral<decltype(b)>()
    );
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    using work_t           = decltype(work_type(work_type(a, b), Out_T{0}));
    const work_t worka     = static_cast<work_t>(a);
    const work_t workb     = static_cast<work_t>(b);
    const work_t workmin   = static_cast<work_t>(outmin);

    if constexpr (core::config::COMPILER_IS_GCC_LIKE
                  && !core::config::FORCE_GENERIC_IMPL) {
        Out_T res = 0;
        if ((!__builtin_sub_overflow(a, b, &res)) || (MR == MathRule::ALLOW)) {
            return core::math::numeric_cast<Out_T, MR>(res);
        } else if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(RG_OOR_STRING);
        } else if constexpr (MR == MathRule::CLAMP) {
            if (std::cmp_greater(workb, workmin + worka)) {
                return outmin;
            } else {
                return outmax;
            }
        }
    } else {
        if (std::cmp_equal(b, 0) || MR == MathRule::ALLOW) {
            return core::math::numeric_cast<Out_T, MR>(worka - workb);
        }
        if (std::cmp_less(b, 0)) {
            if (std::cmp_greater_equal(a, b)) {
                return core::math::numeric_cast<Out_T, MR>(worka - workb);
            }
            if (std::cmp_less(worka - workb, a)) {
                if (MR == MathRule::STRICT) {
                    throw core::exception::Condition(RG_OOR_STRING);
                } else {
                    return outmax;
                }
            }
        }
        if (std::cmp_greater(b, 0) && std::cmp_greater(worka - workb, a)) {
            if (MR == MathRule::STRICT) {
                throw core::exception::Condition(RG_OOR_STRING);
            } else {
                return outmin;
            }
        }
        return core::math::numeric_cast<Out_T, MR>(worka - workb);
    }
}

#undef RG_OOR_STRING
} // namespace core::math
