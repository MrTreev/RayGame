#include "raygame/core/math/ring_average.h" // IWYU pragma: keep
#include "raygame/core/concepts.h"
#include "raytest/raytest.h"
#include <algorithm>
#include <deque>
#include <numeric>
#include <random>

namespace {
using core::math::RingAverage;
constexpr size_t MULT{10ULL};
constexpr size_t BUFLEN{60ULL};

template<typename T>
class RingAverageTest: public ::testing::Test {
public:
    T val() { return 1; }
};

RG_TYPED_TEST_SUITE(RingAverageTest, ::test::types::Integral);

RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
RAYGAME_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")
RAYGAME_CLANG_SUPPRESS_WARNING("-Wunused-template")

template<core::concepts::Number T>
T dice() {
    static std::uniform_int_distribution<T> distr{test::min<T>(), test::max<T>()};
    static std::random_device               device{};
    static std::mt19937                     engine{device()};
    return distr(engine);
}

RAYGAME_CLANG_SUPPRESS_WARNING_POP
} // namespace

RG_TYPED_TEST(RingAverageTest, FPS) {
    RingAverage<size_t, BUFLEN>       ringave;
    std::deque<size_t>                queue{};
    std::array<size_t, BUFLEN * MULT> rands{};
    std::ranges::generate(rands, dice<size_t>);
    for (const size_t val: rands) {
        ringave.add(val);
        queue.push_back(val);
        if (queue.size() > BUFLEN) {
            queue.pop_front();
        }
        const size_t sum      = (std::accumulate(queue.cbegin(), queue.cend(), 0ULL));
        const size_t calc_ave = sum / queue.size();
        RG_CHECK_EQ(calc_ave, ringave.average());
    }
}

RG_TYPED_TEST(RingAverageTest, Averages) {
    using T = decltype(this->val());
    RingAverage<T, BUFLEN>       ringave;
    std::deque<T>                queue{};
    std::array<T, BUFLEN * MULT> rands{};
    std::ranges::generate(rands, dice<T>);
    for (const T val: rands) {
        ringave.add(val);
        queue.push_back(val);
        if (queue.size() > BUFLEN) {
            queue.pop_front();
        }
        const T sum      = std::accumulate(queue.cbegin(), queue.cend(), static_cast<T>(0));
        const T calc_ave = sum / static_cast<T>(queue.size());
        RG_CHECK_EQ(calc_ave, ringave.average());
    }
}
