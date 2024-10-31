#include "core/base/logger.h"
#include "core/math/arithmetic/safe_sub.h"
#include <limits>

int main() {
    using a_t        = long;
    using b_t        = unsigned char;
    volatile b_t sub = 1;
    try {
        auto res = core::math::safe_sub<a_t, core::math::MathRule::STRICT>(
            std::numeric_limits<a_t>::lowest(),
            sub
        );
        core::log::debug(std::format("res: {}", res));
    } catch (...) {}
    auto res = core::math::safe_sub<a_t, core::math::MathRule::CLAMP>(
        std::numeric_limits<a_t>::lowest(),
        sub
    );
    core::log::debug(std::format("res: {}", res));
}
