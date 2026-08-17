#include "raygame/core/assert.hpp"
#include "raytest/raytest.hpp"

RT_TEST(Assert, Checks) {
    RT_SUBCASE("check asserts") {
        RT_CHECK_NO_THROW(RAYGAME_ASSERT(true));
        EXPECT_DEATH({ RAYGAME_ASSERT(false); }, "");
    }
}
