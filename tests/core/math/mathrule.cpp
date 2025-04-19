#include "raygame/core/math/mathrule.h"
#include "raytest/tests_begin.h"

TEST_SUITE("core::math::MathRule") {
    using core::math::MathRule::ALLOW;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    TEST_CASE("core::to_string") {
        CHECK_EQ(core::to_string(CLAMP), "CLAMP");
        CHECK_EQ(core::to_string(ALLOW), "ALLOW");
        CHECK_EQ(core::to_string(STRICT), "STRICT");
    }
}
