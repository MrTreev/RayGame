#include "core/math/arithmetic/safe_sub.h"
#include <limits>

constexpr long l_min = std::numeric_limits<long>::lowest();

int main() {
    const uint8_t sub = 1U;
    volatile long res = 0;
    res += core::math::safe_sub<long, core::math::MathRule::CLAMP>(l_min, sub);

    res += 1;

    res += core::math::safe_sub<long, core::math::MathRule::CLAMP>(l_min, sub);

    res += 1;
}
