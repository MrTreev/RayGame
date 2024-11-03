#pragma once
#include "core/base/config.h"
#include "core/base/debug.h"
#include "core/base/exception.h"
#include "core/base/logger.h"
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
Out_T __attribute__((noinline)) safe_sub(const auto a, const auto b) {
    static_assert(
        std::is_integral<Out_T>() && std::is_integral<decltype(a)>()
        && std::is_integral<decltype(b)>()
    );
    using work_t = decltype(work_type(work_type(a, b), Out_T{0}));

    constexpr Out_T  outmax  = std::numeric_limits<Out_T>::max();
    constexpr Out_T  outmin  = std::numeric_limits<Out_T>::lowest();
    constexpr work_t workmin = static_cast<work_t>(outmin);
    constexpr work_t workmax = static_cast<work_t>(outmin);

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
        if (std::cmp_greater(a, 0)) {
            core::log::debug("a > 0");
            if (std::cmp_greater(b, 0)) {
                core::log::debug("b > 0");
                core::log::debug(
                    std::format("workmin + worka: {}", workmin + worka)
                );
                core::log::debug(
                    std::format("workmax - worka: {}", workmax - worka)
                );
                if (std::cmp_greater(b, workmin + worka)) {
                    core::log::debug("b > workmin + worka");
                    if constexpr (MR == MathRule::STRICT) {
                        throw core::exception::Condition(RG_OOR_STRING);
                    }
                    if constexpr (MR == MathRule::CLAMP) {
                        return outmin;
                    }
                }
            } else {
                if (std::cmp_greater(-b, workmax - worka)) {
                    core::log::debug("-b > workmax - worka");
                    if constexpr (MR == MathRule::STRICT) {
                        throw core::exception::Condition(RG_OOR_STRING);
                    }
                    if constexpr (MR == MathRule::CLAMP) {
                        return outmax;
                    }
                }
            }
        } else {
        }
        return core::math::numeric_cast<Out_T, MR>(worka - workb);
    }
    RAYGAME_UNREACHABLE;
}

#undef RG_OOR_STRING
} // namespace core::math
