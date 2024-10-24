#include "core/math/random.h" // IWYU pragma: keep
#include "core/base/condition.h"
#include <random>

namespace {

#if defined(RAYGAME_USE_FULL_RANDOM)
constexpr bool random_seed = true;
#else
constexpr bool random_seed = false;
#endif
uint64_t seed = 42;

// Disable global constructor warnings for global random_device, as it is a singleton anyway
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
std::random_device dev;
#pragma clang diagnostic pop

uint64_t rand_seed() {
    if constexpr (random_seed) {
        return dev();
    } else {
        ++seed;
        return seed;
    }
}
} // namespace

template<>
std::vector<uint8_t>
core::math::rand_n(size_t amount, uint8_t min, uint8_t max) {
    RAYGAME_PRE_CONDITION(min < max);
    std::mt19937                           rng(rand_seed());
    std::uniform_int_distribution<uint8_t> dist(min, max);
    std::vector<uint8_t>                   results;
    results.reserve(amount);
    while (results.size() < amount) {
        results.push_back(dist(rng));
    }
    return results;
}

template<>
uint8_t rand(uint8_t min, uint8_t max) {
    RAYGAME_PRE_CONDITION(min < max);
    std::mt19937                           rng(rand_seed());
    std::uniform_int_distribution<uint8_t> dist(min, max);
    return dist(rng);
}

#if defined(RAYGAME_ENABLE_TESTS)
#    include "test/tests_begin.h"

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
#endif
