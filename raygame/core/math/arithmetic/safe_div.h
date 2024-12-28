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
template<std::integral Out_T, MathRule MR = core::math::MR_DEFAULT>
constexpr Out_T
safe_div(const std::integral auto aval, const std::integral auto bval) {
    if (std::cmp_equal(bval, 0)) {
        throw core::exception::Condition("Cannot divide by zero");
    }
    if (std::cmp_equal(bval, -1)
        && std::cmp_equal(aval, std::numeric_limits<Out_T>::lowest())) {
        if constexpr (MR == MathRule::STRICT) {
            throw core::exception::Condition(std::format(
                "Result of division ({} / {}) would overflow for output type "
                "'{}'",
                aval,
                bval,
                core::debug::type_name<Out_T>()
            ));
        } else if constexpr (MR == MathRule::CLAMP) {
            return std::numeric_limits<Out_T>::max();
        }
    }
    if constexpr (std::is_signed<decltype(aval)>()
                  == std::is_signed<decltype(bval)>()) {
        return core::math::numeric_cast<Out_T, MR>(aval / bval);
    } else {
        using work_t = decltype(work_type(work_type(aval, bval), Out_T{}));
        return core::math::numeric_cast<Out_T, MR>(
            static_cast<work_t>(aval) / static_cast<work_t>(bval)
        );
    }
}

} // namespace core::math
