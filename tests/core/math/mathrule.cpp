#include "raygame/core/math/mathrule.h"
#include "raytest/raytest.h"

using core::math::MathRule::ALLOW;
using core::math::MathRule::CLAMP;
using core::math::MathRule::STRICT;

RT_TEST(MathRule, ToString) {
    RT_CHECK_EQ(core::to_string(CLAMP), "CLAMP");
    RT_CHECK_EQ(core::to_string(ALLOW), "ALLOW");
    RT_CHECK_EQ(core::to_string(STRICT), "STRICT");
}
