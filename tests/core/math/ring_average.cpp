#include "raygame/core/math/ring_average.h" // IWYU pragma: keep
#include "raytest/raytest.h"
#include <ranges>

namespace {
using core::math::RingAverage;
constexpr size_t BUFLEN{60ULL};

template<typename T>
class RingAverageTest: public ::testing::Test {
public:
    void test_vals(
        std::array<T, BUFLEN> values,
        std::array<T, BUFLEN> averages,
        std::array<T, BUFLEN> min_vals,
        std::array<T, BUFLEN> max_vals
    ) {
        using T = decltype(this->val());
        RingAverage<T, BUFLEN> ringave;
        for (const auto [val, ave, max, min]:
             std::ranges::zip_view(values, averages, max_vals, min_vals)) {
            ringave.add(val);
            RG_CHECK_EQ(ringave.average(), ave);
            RG_CHECK_EQ(ringave.max(), max);
            RG_CHECK_EQ(ringave.min(), min);
        }
    }

    T val() { return 1; }
};

RG_TYPED_TEST_SUITE(RingAverageTest, ::test::types::Integral);
} // namespace

RG_TYPED_TEST(RingAverageTest, Stats) {
    using T = decltype(this->val());
    RingAverage<T, BUFLEN>      ringave;
    const std::array<T, BUFLEN> values = {
        {0, 0, 0}
    };
    const std::array<T, BUFLEN> averages = {
        {0, 0, 0}
    };
    const std::array<T, BUFLEN> max_vals = {
        {0, 0, 0}
    };
    const std::array<T, BUFLEN> min_vals = {
        {0, 0, 0}
    };
    for (const auto [val, ave, max, min]:
         std::ranges::zip_view(values, averages, max_vals, min_vals)) {
        ringave.add(val);
        RG_CHECK_EQ(ringave.average(), ave);
        RG_CHECK_EQ(ringave.max(), max);
        RG_CHECK_EQ(ringave.min(), min);
    }
}
