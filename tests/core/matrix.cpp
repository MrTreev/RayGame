#include "raygame/core/matrix.h" // IWYU pragma: keep
#include "raytest/raytest.h"

TEST_CASE("core::Matrix") {
    SUBCASE("Construction") {
        const core::Matrix<int, 2, 2> item{0, 1, 2, 4};
    }
    SUBCASE("multi-dim read") {
        const core::Matrix<int, 2, 2> item{0, 1, 2, 4};
        CHECK_EQ(item[0, 0], 0);
        CHECK_EQ(item[1, 0], 1);
        CHECK_EQ(item[0, 1], 2);
        CHECK_EQ(item[1, 1], 4);
    }
    SUBCASE("multi-dim write") {
        core::Matrix<int, 2, 2> item{0, 0, 0, 0};
        item[0, 0] = 1;
        item[1, 0] = 2;
        item[0, 1] = 3;
        item[1, 1] = 4;
        CHECK_EQ(item[0, 0], 1);
        CHECK_EQ(item[1, 0], 2);
        CHECK_EQ(item[0, 1], 3);
        CHECK_EQ(item[1, 1], 4);
    }
}
