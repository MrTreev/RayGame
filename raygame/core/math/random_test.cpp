#include "raygame/core/math/random.h" // IWYU pragma: keep
#include "raygame/core/test/tests_begin.h"
#include <array>

TEST_SUITE("core::math::rand") {
    using core::math::rand;
    using test::all_same;
    constexpr size_t TEST_LEN = 16;
    TEST_CASE_TEMPLATE("std::vector", T, FWINTS) {
        const T                 max_rand = 1;
        const T                 min_rand = 0;
        std::array<T, TEST_LEN> test_arr{};
        for (auto& val: test_arr) {
            val = rand(min_rand, max_rand);
        }
        CHECK_FALSE(all_same(test_arr));
        CHECK_UNARY(std::all_of(test_arr.begin(), test_arr.end(), [](auto val) {
            return val >= min_rand;
        }));
        CHECK_UNARY(std::all_of(test_arr.begin(), test_arr.end(), [](auto val) {
            return val <= max_rand;
        }));
    }
}

TEST_SUITE("core::math::rand_n") {
    using core::math::rand_n;
    using test::all_same;
    constexpr size_t TEST_LEN = 16;
    TEST_CASE_TEMPLATE("std::vector", T, FWINTS) {
        const T        max_rand = 1;
        const T        min_rand = 0;
        std::vector<T> test_vec = rand_n<T>(TEST_LEN);
        CHECK_EQ(test_vec.size(), TEST_LEN);
        CHECK_FALSE(all_same(test_vec));
        std::vector<T> rand_01 = rand_n<T>(TEST_LEN, min_rand, max_rand);
        CHECK_EQ(rand_01.size(), TEST_LEN);
        CHECK_FALSE(all_same(rand_01));
        for (const auto& val: rand_01) {
            CHECK_GE(val, min_rand);
            CHECK_LE(val, max_rand);
        }
    }
}
