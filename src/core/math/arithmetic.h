#pragma once
#include "core/exception.h"
#include "core/math.h"
#include <concepts>
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

//! Add two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<
    typename Out_T,
    MathRule MR = core::math::MR_DEFAULT,
    typename A_T,
    typename B_T>
requires(std::integral<Out_T> && std::integral<A_T> && std::integral<B_T>)
inline constexpr Out_T safe_add(A_T a, B_T b) {
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    if (std::cmp_greater(a, 0) && std::cmp_greater(b, outmax - a)) {
        if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(std::format(
                "Result of addition ({} + {}) is above the max for output type "
                "'{}'",
                a,
                b,
                core::debug::type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmax;
        }
    } else if (std::cmp_less(a, 0) && std::cmp_less(b, outmin - a)) {
        if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(std::format(
                "Result of addition ({} + {}) is below the min for output type "
                "'{}'",
                a,
                b,
                core::debug::type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmin;
        }
    }
    return core::math::numeric_cast<Out_T, MR>(a + b);
}

//! Subtract two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<
    typename Out_T,
    MathRule MR = core::math::MR_DEFAULT,
    typename A_T,
    typename B_T>
requires(std::integral<Out_T> && std::integral<A_T> && std::integral<B_T>)
inline constexpr Out_T safe_sub(A_T a, B_T b) {
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    if (std::cmp_less(a, 0) && std::cmp_greater(b, outmax + a)) {
        if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(std::format(
                "Result of subtraction ({} - {}) is above the max for output "
                "type '{}'",
                a,
                b,
                core::debug::type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmax;
        }
    } else if (std::cmp_greater(a, 0) && std::cmp_less(b, outmin + a)) {
        if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(std::format(
                "Result of subtraction ({} - {}) is below the min for output "
                "type '{}'",
                a,
                b,
                core::debug::type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmin;
        }
    }
    return core::math::numeric_cast<Out_T, MR>(a + b);
}

//! Divide two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<
    typename Out_T,
    MathRule MR = core::math::MR_DEFAULT,
    typename A_T,
    typename B_T>
requires(std::integral<Out_T> && std::integral<A_T> && std::integral<B_T>)
inline constexpr Out_T safe_div(A_T a, B_T b) {
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    if (std::cmp_equal(b, 0)) {
        throw core::exception::Condition("Cannot divide by zero");
    }
    if (std::cmp_equal(b, -1) && std::cmp_equal(a, outmin)) {
        if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(std::format(
                "Result of division ({} / {}) would overflow for output type "
                "'{}'",
                a,
                b,
                core::debug::type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmax;
        }
    }
    if constexpr (std::is_signed_v<A_T> == std::is_signed_v<B_T>) {
        return core::math::numeric_cast<Out_T, MR>(a / b);
    } else if constexpr (std::is_signed_v<A_T>) {
        return core::math::numeric_cast<Out_T, MR>(make_signed(a) / b);
    } else if constexpr (std::is_signed_v<B_T>) {
        return core::math::numeric_cast<Out_T, MR>(a / make_signed(b));
    }
}

//! Multiply two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
requires(std::integral<Out_T>)
inline constexpr Out_T safe_mult(auto a, auto b) {
    static_assert(std::is_integral_v<Out_T> && std::is_integral_v<decltype(a)> && std::is_integral_v<decltype(b)>);
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    if ((std::cmp_not_equal(a, 0) && std::cmp_greater(b, outmax / a))
        || (std::cmp_equal(a, -1) && std::cmp_equal(b, outmin))
        || (std::cmp_equal(b, -1) && std::cmp_equal(a, outmin))) {
        if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(std::format(
                "Result of subtraction ({} - {}) is above the max for "
                "output "
                "type '{}'",
                a,
                b,
                core::debug::type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmax;
        }
    } else if (std::cmp_not_equal(a, 0)
               && std::cmp_less(
                   b,
                   safe_div<decltype(max_type(a, b))>(outmin, a)
               )) {
        if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(std::format(
                "Result of subtraction ({} - {}) is below the min for output "
                "type '{}'",
                a,
                b,
                core::debug::type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmin;
        }
    }
    return core::math::numeric_cast<Out_T, MR>(a * b);
}

} // namespace core::math
