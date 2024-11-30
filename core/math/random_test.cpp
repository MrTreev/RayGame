#include "core/math/random.h" // IWYU pragma: keep
#include "test/tests_begin.h"

TEST_SUITE("core::math::rand_n") {
    using core::math::rand_n;
    using test::all_same;
    constexpr size_t test_len = 16;
    TEST_CASE_TEMPLATE("std::vector", T, FWINTS) {
        const T max_rand = 1;
        const T min_rand = 0;

        std::vector<T> rands = rand_n<T>(test_len);
        CHECK_EQ(rands.size(), test_len);
        CHECK_FALSE(all_same(rands));
        std::vector<T> rand_01 = rand_n<T>(test_len, min_rand, max_rand);
        CHECK_EQ(rand_01.size(), test_len);
        CHECK_FALSE(all_same(rand_01));
        for (const auto& val: rand_01) {
            CHECK_GE(val, min_rand);
            CHECK_LE(val, max_rand);
        }
    }
}
