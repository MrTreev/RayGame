#include "raygame/core/matrix.h" // IWYU pragma: keep
#include "raytest/raytest.h"

RT_TEST(Matrix, Basic) {
    RT_SUBCASE("Construction") {
        const core::Matrix<int, 2, 2> item{0, 1, 2, 4};
    }
    RT_SUBCASE("multi-dim read") {
        const core::Matrix<int, 2, 2> item{0, 1, 2, 4};
        RT_CHECK_EQ((item[0, 0]), 0);
        RT_CHECK_EQ((item[1, 0]), 1);
        RT_CHECK_EQ((item[0, 1]), 2);
        RT_CHECK_EQ((item[1, 1]), 4);
    }
    RT_SUBCASE("multi-dim write") {
        core::Matrix<int, 2, 2> item{0, 0, 0, 0};
        item[0, 0] = 1;
        item[1, 0] = 2;
        item[0, 1] = 3;
        item[1, 1] = 4;
        RT_CHECK_EQ((item[0, 0]), 1);
        RT_CHECK_EQ((item[1, 0]), 2);
        RT_CHECK_EQ((item[0, 1]), 3);
        RT_CHECK_EQ((item[1, 1]), 4);
    }
}
