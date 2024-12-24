#pragma once
#include "raygame/core/debug.h"
#include "raygame/core/exception.h"
#include "raygame/core/math/math.h"
#include "raygame/core/math/numeric_cast.h"
#include <limits>
#include <type_traits>
#include <utility>

namespace core::math {

//! Divide two numeric types ensuring no undesired change in value
/*!
 * @tparam MR Defines the out-of-range behaviour
 * @pre @a b is not zero
 */
template<typename Out_T, MathRule MR = core::math::MR_DEFAULT>
constexpr Out_T safe_div(const auto a, const auto b) {
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
        using work_t       = decltype(work_type(work_type(a, b), Out_T{}));
        const work_t worka = static_cast<work_t>(a);
        const work_t workb = static_cast<work_t>(b);
        return numeric_cast<Out_T, MR>(worka / workb);
    }
}

} // namespace core::math
