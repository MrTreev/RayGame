#include "raygame/core/matrix.h" // IWYU pragma: keep
#include "raytest/raytest.h"
#define RG_TEST_FILE Matrix

RG_TEST(Matrix, Basic) {
    RG_SUBCASE("Construction") {
        const core::Matrix<int, 2, 2> item{0, 1, 2, 4};
    }
    RG_SUBCASE("multi-dim read") {
        const core::Matrix<int, 2, 2> item{0, 1, 2, 4};
        RG_CHECK_EQ((item[0, 0]), 0);
        RG_CHECK_EQ((item[1, 0]), 1);
        RG_CHECK_EQ((item[0, 1]), 2);
        RG_CHECK_EQ((item[1, 1]), 4);
    }
    RG_SUBCASE("multi-dim write") {
        core::Matrix<int, 2, 2> item{0, 0, 0, 0};
        item[0, 0] = 1;
        item[1, 0] = 2;
        item[0, 1] = 3;
        item[1, 1] = 4;
        RG_CHECK_EQ((item[0, 0]), 1);
        RG_CHECK_EQ((item[1, 0]), 2);
        RG_CHECK_EQ((item[0, 1]), 3);
        RG_CHECK_EQ((item[1, 1]), 4);
    }
}
