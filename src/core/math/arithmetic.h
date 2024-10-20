#pragma once
#include "core/base/config.h"
#include "core/base/debug.h"
#include "core/base/exception.h"
#include "core/math/math.h"
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
inline constexpr Out_T safe_add(const auto a, const auto b) {
    static_assert(
        std::is_integral<Out_T>() && std::is_integral<decltype(a)>()
        && std::is_integral<decltype(b)>()
    );
    using core::debug::type_name;
    using core::exception::Condition;
    using core::math::numeric_cast;
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();

    if constexpr (core::config::COMPILER_IS_GCC_LIKE) {
        Out_T res = 0;
        if (!__builtin_add_overflow(a, b, &res)) {
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
            if (std::cmp_greater(b, outmax - a)
                || std::cmp_greater(a, outmax - b)) {
                return outmax;
            } else {
                return outmin;
            }
        } else if constexpr (MR == MathRule::ALLOW) {
            return res;
        }
    } else {
        if (std::cmp_greater(a, 0) && std::cmp_greater(b, outmax - a)) {
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
        } else if (std::cmp_less(a, 0) && std::cmp_less(b, outmin - a)) {
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
        return numeric_cast<Out_T, MR>(a + b);
    }
}

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
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();
    using core::debug::type_name;
    using core::exception::Condition;
    using core::math::numeric_cast;

    if constexpr (core::config::COMPILER_IS_GCC_LIKE) {
        Out_T res = 0;
        if (!__builtin_sub_overflow(a, b, &res)) {
            return res;
        } else if constexpr (MR == MathRule::STRICT) {
            throw Condition(std::format(
                "Result of subtraction ({} - {}) is outside the range of "
                "output type '{}'",
                a,
                b,
                type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            if (std::cmp_greater(b, outmin + a)
                || std::cmp_greater(a, outmin + b)) {
                return outmin;
            } else {
                return outmax;
            }
        } else if constexpr (MR == MathRule::ALLOW) {
            return res;
        }
    } else {
        if (std::cmp_less(a, 0) && std::cmp_greater(b, outmax + a)) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of subtraction ({} - {}) is above the max for "
                    "output "
                    "type '{}'",
                    a,
                    b,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmax;
            }
        } else if (std::cmp_greater(a, 0) && std::cmp_less(b, outmin + a)) {
            if constexpr (MR == MathRule::STRICT) {
                throw Condition(std::format(
                    "Result of subtraction ({} - {}) is below the min for "
                    "output type '{}'",
                    a,
                    b,
                    type_name<Out_T>()
                ));
            } else if constexpr (MR == MathRule::CLAMP) {
                return outmin;
            }
        }
        return numeric_cast<Out_T, MR>(a + b);
    }
}

//! Divide two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
requires(std::integral<Out_T>)
inline constexpr Out_T safe_div(const auto a, const auto b) {
    static_assert(
        std::is_integral<Out_T>() && std::is_integral<decltype(a)>()
        && std::is_integral<decltype(b)>()
    );
    using core::debug::type_name;
    using core::exception::Condition;
    using core::math::numeric_cast;
    constexpr Out_T outmax = std::numeric_limits<Out_T>::max();
    constexpr Out_T outmin = std::numeric_limits<Out_T>::lowest();

    if (std::cmp_equal(b, 0)) {
        throw Condition("Cannot divide by zero");
    }
    if (std::cmp_equal(b, -1) && std::cmp_equal(a, outmin)) {
        if constexpr (MR == MathRule::STRICT) {
            throw Condition(std::format(
                "Result of division ({} / {}) would overflow for output type "
                "'{}'",
                a,
                b,
                type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return outmax;
        }
    }
    if constexpr (std::is_signed<decltype(a)>()
                  == std::is_signed<decltype(b)>()) {
        return numeric_cast<Out_T, MR>(a / b);
    } else {
        const auto maxs = max_type(a, b);
        return numeric_cast<Out_T, MR>(maxs.x / maxs.y);
    }
}

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

    if constexpr (core::config::COMPILER_IS_GCC_LIKE) {
        Out_T res = 0;
        if (!__builtin_mul_overflow(a, b, &res)) {
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
        } else if constexpr (MR == MathRule::ALLOW) {
            return res;
        }
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
