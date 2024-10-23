#pragma once
#include "core/base/debug.h"
#include "core/base/exception.h"
#include "core/math/math.h"
#include "core/math/numeric_cast.h"
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

//! Divide two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
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

} // namespace core::math
