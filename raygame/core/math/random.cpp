#include "raygame/core/math/random.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include <format>
#include <random>

namespace {

#if defined(RAYGAME_USE_FULL_RANDOM)
constexpr bool random_seed = true;
#else
constexpr bool random_seed = false;
#endif

#if !defined(RAYGAME_RANDOM_INITIAL_SEED)
constexpr auto STARTING_SEED = 42;
#else
constexpr auto STARTING_SEED = RAYGAME_RANDOM_INITIAL_SEED;
#endif
[[maybe_unused]]
uint64_t seed = STARTING_SEED; //NOLINT(*-non-const-global-variables)

// Disable global constructor warnings for global random_device, as it is a singleton anyway
RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
RAYGAME_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")
// Done like this because there should only be a single random_device for the
// whole game
std::random_device dev; // NOLINT(cert-err58-cpp,*-non-const-global-variables)
RAYGAME_CLANG_SUPPRESS_WARNING_POP

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
    core::condition::pre_condition(
        min < max,
        std::format("min: {} < max: {}", min, max)
    );
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
    core::condition::pre_condition(
        min < max,
        std::format("min: {} < max: {}", min, max)
    );
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
