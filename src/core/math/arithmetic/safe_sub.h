#pragma once
#include "core/base/config.h"
#include "core/base/debug.h"
#include "core/base/exception.h"
#include "core/math/arithmetic/safe_add.h"
#include "core/math/math.h"
#include "core/math/numeric_cast.h"
#include <concepts>
#include <cstdlib>
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
Out_T __attribute__((noinline)) safe_sub(const auto a, const auto b) {
    static_assert(
        std::is_integral<Out_T>() && std::is_integral<decltype(a)>()
        && std::is_integral<decltype(b)>()
    );
    using work_t = decltype(work_type(work_type(a, b), Out_T{0}));

    constexpr Out_T  outmax  = std::numeric_limits<Out_T>::max();
    constexpr Out_T  outmin  = std::numeric_limits<Out_T>::lowest();
    constexpr work_t workmin = static_cast<work_t>(outmin);

    const work_t worka = static_cast<work_t>(a);
    const work_t workb = static_cast<work_t>(b);

    if constexpr (core::config::COMPILER_IS_GCC_LIKE
                  && !core::config::FORCE_GENERIC_IMPL) {
        Out_T res = 0;
        if (__builtin_sub_overflow(a, b, &res)) {
            if constexpr (MR == MathRule::ALLOW) {
                return core::math::numeric_cast<Out_T, MR>(res);
            }
            if constexpr (MR == MathRule::STRICT) {
                throw core::exception::Condition(RG_OOR_STRING);
            }
            if constexpr (MR == MathRule::CLAMP) {
                if (std::cmp_greater(workb, workmin + worka)) {
                    return outmin;
                } else {
                    return outmax;
                }
            }
            RAYGAME_UNREACHABLE;
        } else {
            return core::math::numeric_cast<Out_T, MR>(res);
        }
    } else {
        if constexpr (MR == MathRule::ALLOW) {
            return core::math::numeric_cast<Out_T, MR>(worka - workb);
        }
        if (std::cmp_equal(b, a)) {
            return 0;
        }
        if (std::cmp_equal(a, 0)) {
            return core::math::numeric_cast<Out_T, MR>(-b);
        }
        if (std::cmp_equal(b, 0)) {
            return core::math::numeric_cast<Out_T, MR>(a);
        }
        if (std::is_unsigned<work_t>()) {
            if (a >= b) {
                return numeric_cast<Out_T, MR>(worka - workb);
            }
            if constexpr (MR == MathRule::STRICT) {
                throw core::exception::Condition(RG_OOR_STRING);
            }
            if (MR == MathRule::CLAMP) {
                return outmin;
            }
        }
        return safe_add<Out_T, MR>(worka, -workb);
    }
    RAYGAME_UNREACHABLE;
}

#undef RG_OOR_STRING
} // namespace core::math
