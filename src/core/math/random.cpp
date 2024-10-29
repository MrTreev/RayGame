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

template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
T core::math::rand(T min, T max) {
    RAYGAME_PRE_CONDITION(min < max);
    std::mt19937                     rng(rand_seed());
    std::uniform_int_distribution<T> dist(min, max);
    return dist(rng);
}

template uint8_t  core::math::rand(uint8_t min, uint8_t max);
template uint16_t core::math::rand(uint16_t min, uint16_t max);
template uint32_t core::math::rand(uint32_t min, uint32_t max);
template uint64_t core::math::rand(uint64_t min, uint64_t max);
template int8_t   core::math::rand(int8_t min, int8_t max);
template int16_t  core::math::rand(int16_t min, int16_t max);
template int32_t  core::math::rand(int32_t min, int32_t max);
template int64_t  core::math::rand(int64_t min, int64_t max);

template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
std::vector<T> core::math::rand_n(size_t amount, T min, T max) {
    RAYGAME_PRE_CONDITION(min < max);
    std::mt19937                     rng(rand_seed());
    std::uniform_int_distribution<T> dist(min, max);
    std::vector<T>                   results;
    results.reserve(amount);
    while (results.size() < amount) {
        results.push_back(dist(rng));
    }
    return results;
}

template std::vector<uint8_t>
core::math::rand_n(size_t amount, uint8_t min, uint8_t max);
template std::vector<uint16_t>
core::math::rand_n(size_t amount, uint16_t min, uint16_t max);
template std::vector<uint32_t>
core::math::rand_n(size_t amount, uint32_t min, uint32_t max);
template std::vector<uint64_t>
core::math::rand_n(size_t amount, uint64_t min, uint64_t max);
template std::vector<int8_t>
core::math::rand_n(size_t amount, int8_t min, int8_t max);
template std::vector<int16_t>
core::math::rand_n(size_t amount, int16_t min, int16_t max);
template std::vector<int32_t>
core::math::rand_n(size_t amount, int32_t min, int32_t max);
template std::vector<int64_t>
core::math::rand_n(size_t amount, int64_t min, int64_t max);

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
