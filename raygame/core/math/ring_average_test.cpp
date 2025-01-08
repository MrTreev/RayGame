#include "raygame/core/concepts.h"
#include "raygame/core/math/ring_average.h" // IWYU pragma: keep
#include "raygame/core/test/tests_begin.h"
#include <algorithm>
#include <deque>
#include <numeric>
#include <random>

namespace {
RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
RAYGAME_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")

template<core::concepts::Number T>
T dice() {
    static std::uniform_int_distribution<T> distr{
        test::min<T>(),
        test::max<T>()
    };
    static std::random_device device{};
    static std::mt19937       engine{device()};
    return distr(engine);
}

RAYGAME_CLANG_SUPPRESS_WARNING_POP
} // namespace

TEST_SUITE("core::math::ring_average") {
    using core::math::RingAverage;
    TEST_CASE("FPS Counter") {
        constexpr size_t                  buflen = 60ULL;
        constexpr size_t                  mult   = 10ULL;
        RingAverage<size_t, buflen>       ringave;
        std::deque<size_t>                queue{};
        std::array<size_t, buflen * mult> rands{};
        std::ranges::generate(rands, dice<size_t>);
        for (const size_t val: rands) {
            ringave.add(val);
            queue.push_back(val);
            if (queue.size() > buflen) {
                queue.pop_front();
            }
            const size_t sum =
                (std::accumulate(queue.cbegin(), queue.cend(), 0ULL));
            const size_t calc_ave = sum / queue.size();
            CHECK_EQ(calc_ave, ringave.average());
        }
    }
    TEST_CASE_TEMPLATE("RingAverage", T, FWINTS) {
        constexpr size_t             buflen = 60ULL;
        constexpr size_t             mult   = 10ULL;
        RingAverage<T, buflen>       ringave;
        std::deque<T>                queue{};
        std::array<T, buflen * mult> rands{};
        std::ranges::generate(rands, dice<T>);
        for (const T val: rands) {
            ringave.add(val);
            queue.push_back(val);
            if (queue.size() > buflen) {
                queue.pop_front();
            }
            const T sum      = (std::accumulate(
                queue.cbegin(),
                queue.cend(),
                static_cast<T>(0)
            ));
            const T calc_ave = sum / static_cast<T>(queue.size());
            CHECK_EQ(calc_ave, ringave.average());
        }
    }
}
