#include "raygame/core/math/mathrule.h"
#include "raytest/raytest.h"

using core::math::MathRule::ALLOW;
using core::math::MathRule::CLAMP;
using core::math::MathRule::STRICT;

RG_TEST(MathRule, ToString) {
    RG_CHECK_EQ(core::to_string(CLAMP), "CLAMP");
    RG_CHECK_EQ(core::to_string(ALLOW), "ALLOW");
    RG_CHECK_EQ(core::to_string(STRICT), "STRICT");
}
