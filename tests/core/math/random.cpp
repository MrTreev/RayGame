#include "raygame/core/math/random.h" // IWYU pragma: keep
#include "raytest/raytest.h"
#include <array>

template<typename T>
class Rand: public ::testing::Test {
public:
    T val() { return 1; }
};

RT_TYPED_TEST_SUITE(Rand, test::types::Integral);

using core::math::rand;
using core::math::rand_n;
using test::all_same;
constexpr size_t TEST_LEN = 16;

RT_TYPED_TEST(Rand, Rand) {
    using T = decltype(this->val());
    const T                 max_rand{1};
    const T                 min_rand{0};
    std::array<T, TEST_LEN> test_arr{};
    for (auto& val: test_arr) {
        val = rand(min_rand, max_rand);
    }
    RT_CHECK_FALSE(all_same(test_arr));
    RT_CHECK_TRUE(std::all_of(test_arr.begin(), test_arr.end(), [](auto val) {
        return val >= min_rand;
    }));
    RT_CHECK_TRUE(std::all_of(test_arr.begin(), test_arr.end(), [](auto val) {
        return val <= max_rand;
    }));
}

RT_TYPED_TEST(Rand, RandN) {
    using T = decltype(this->val());
    const T              max_rand{1};
    const T              min_rand{0};
    const std::vector<T> test_vec = rand_n<T>(TEST_LEN);
    const std::vector<T> rand_01  = rand_n<T>(TEST_LEN, min_rand, max_rand);
    RT_CHECK_EQ(test_vec.size(), TEST_LEN);
    RT_CHECK_FALSE(all_same(test_vec));
    RT_CHECK_EQ(rand_01.size(), TEST_LEN);
    RT_CHECK_FALSE(all_same(rand_01));
    for (const auto& val: rand_01) {
        RT_CHECK_GE(val, min_rand);
        RT_CHECK_LE(val, max_rand);
    }
}
