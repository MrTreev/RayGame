#include "raygame/core/assert.h"
#include "raytest/raytest.h"

RT_TEST(Assert, Checks) {
    RT_SUBCASE("check asserts") {
        RT_CHECK_NO_THROW(RAYGAME_ASSERT(true));
        EXPECT_DEATH({ RAYGAME_ASSERT(false); }, "Assertion kills program");
    }
}
