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
    const std::string oor_string = std::format(
        "Result of subtraction ({} - {}) is outside the range of "
        "output type '{}'",
        a,
        b,
        core::debug::type_name<Out_T>()
    );
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    using core::config::COMPILER_IS_GCC_LIKE;
    using core::config::FORCE_GENERIC_IMPL;
    using core::debug::type_name;
    using core::exception::Condition;
    using core::math::numeric_cast;
    using work_t       = decltype(work_type(work_type(a, b), Out_T{}));
    const auto worka   = static_cast<work_t>(a);
    const auto workb   = static_cast<work_t>(b);
    const auto workmin = static_cast<work_t>(outmin);

    if constexpr (COMPILER_IS_GCC_LIKE && !FORCE_GENERIC_IMPL) {
        Out_T res = 0;
        if ((!__builtin_sub_overflow(a, b, &res)) || (MR == MathRule::ALLOW)) {
            return numeric_cast<Out_T, MR>(res);
        } else if constexpr (MR == MathRule::STRICT) {
            throw Condition(oor_string);
        } else if constexpr (MR == MathRule::CLAMP) {
            if (std::cmp_greater(workb, workmin + worka)) {
                return outmin;
            } else {
                return outmax;
            }
        }
        RAYGAME_ELSE_UNKNOWN("");
    } else {
        if (std::cmp_equal(b, 0) || MR == MathRule::ALLOW) {
            return numeric_cast<Out_T, MR>(worka - workb);
        } else {
            const work_t res = worka - workb;
            if (std::cmp_less(b, 0) && std::cmp_greater_equal(a, b)) {
                return numeric_cast<Out_T, MR>(res);
            } else if (std::cmp_greater(b, 0) && std::cmp_greater(res, a)) {
                if constexpr (MR == MathRule::STRICT) {
                    throw Condition(oor_string);
                } else {
                    return outmin;
                }
            } else if (std::cmp_less(b, 0) && std::cmp_less(res, a)) {
                core::log::debug("max");
                if constexpr (MR == MathRule::STRICT) {
                    throw Condition(oor_string);
                } else {
                    return outmax;
                }
            } else {
                return numeric_cast<Out_T, MR>(res);
            }
        }
    }
}

} // namespace core::math
