#include "raygame/core/matrix.h" // IWYU pragma: keep
#include "raygame/core/test/tests_begin.h"

TEST_SUITE("core::Matrix") {
    TEST_CASE("Construction") {
        const core::Matrix<int, 2, 2> item{
            {0, 1, 2, 4}
        };
    }
}
