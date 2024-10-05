#pragma once
#include "core/condition.h"
#include "core/math.h"

namespace core::math {

//! Add two numeric types ensuring no overflows or underflows
template<
    typename Out_T,
    typename A_T,
    typename B_T,
    MathRule MR = MathRule::STRICT>
inline constexpr Out_T safe_add(A_T a, B_T b) {
    if constexpr (std::is_unsigned_v<A_T> && std::is_unsigned_v<B_T>) {
        const uintmax_t ai  = numeric_cast<uintmax_t>(a);
        const uintmax_t bi  = numeric_cast<uintmax_t>(b);
        const uintmax_t res = ai + bi;
        RG_CHECK_CONDITION((res > a) && (res > b));
        return numeric_cast<Out_T>(res);
    }
    if constexpr (std::is_signed_v<A_T> || std::is_signed_v<B_T>) {
        const intmax_t ai  = numeric_cast<intmax_t>(a);
        const intmax_t bi  = numeric_cast<intmax_t>(b);
        const intmax_t res = ai + bi;
        RG_CHECK_CONDITION((res > a) && (res > b));
        return numeric_cast<Out_T>(res);
    }
}

} // namespace core::math
