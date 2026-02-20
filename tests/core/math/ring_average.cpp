#include "raygame/core/math/ring_average.h" // IWYU pragma: keep
#include "raytest/raytest.h"
#include <ranges>

namespace {
using core::math::RingAverage;

template<typename T>
class RingAverageTest: public ::testing::Test {
public:
    static constexpr size_t BUFLEN{4};

    void test_vals(
        std::initializer_list<T> values,
        std::initializer_list<T> averages,
        std::initializer_list<T> min_vals,
        std::initializer_list<T> max_vals
    ) {
        RingAverage<T, BUFLEN> ringave;
        for (const auto [val, ave, max, min]:
             std::ranges::zip_view(values, averages, max_vals, min_vals)) {
            ringave.add(val);
            RT_CHECK_EQ(ringave.average(), ave);
            RT_CHECK_EQ(ringave.max(), max);
            RT_CHECK_EQ(ringave.min(), min);
        }
    }

    T val() { return 1; }
};

RT_TYPED_TEST_SUITE(RingAverageTest, ::test::types::Integral);
} // namespace

RT_TYPED_TEST(RingAverageTest, Stats) {
    this->test_vals(
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    );
    this->test_vals(
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    );
}
