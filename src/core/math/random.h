#pragma once
#include "core/condition.h"
#include "core/types.h"
#include <limits>
#include <random>

uint64_t rand_seed();

namespace core::math {

namespace detail {

#if defined(RAYGAME_USE_FULL_RANDOM)
constexpr bool random_seed = true;
#else
constexpr bool random_seed = false;
#endif
uint64_t rand_seed();

} // namespace detail

//! Returns an array of N random values in a range
/*!
 * @tparam N number of elements
 * @param min minimum random value
 * @param max maximum random value
 * @return array of N random values in range
 *
 * @pre min < max
 */
template<typename T, size_t N>
requires std::is_integral_v<T> && std::is_trivial_v<T>
inline std::array<T, N> rand_n(
    T min = std::numeric_limits<T>::min(),
    T max = std::numeric_limits<T>::max()
) {
    RG_PRE_CONDITION(min < max);
    std::mt19937                     rng(detail::rand_seed());
    std::uniform_int_distribution<T> dist(min, max);
    std::array<T, N>                 results;
    for (T& res: results) {
        res = dist(rng);
    }
    return results;
}

//! Returns a vector of N random values in a range
/*!
 * @param amount number of elements
 * @param min minimum random value
 * @param max maximum random value
 * @return vector of N random values in range
 *
 * @pre min < max
 */
template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
inline std::vector<T> rand_n(
    size_t amount,
    T      min = std::numeric_limits<T>::min(),
    T      max = std::numeric_limits<T>::max()
) {
    RG_PRE_CONDITION(min < max);
    std::mt19937                     rng(detail::rand_seed());
    std::uniform_int_distribution<T> dist(min, max);
    std::vector<T>                   results;
    results.reserve(amount);
    while (results.size() < amount) {
        results.push_back(dist(rng));
    }
    return results;
}

//! Returns a random value in a range
/*!
 * @param min minimum random value
 * @param max maximum random value
 * @return random value in range
 *
 * @pre min < max
 */
template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
inline T rand(
    T min = std::numeric_limits<T>::min(),
    T max = std::numeric_limits<T>::max()
) {
    RG_PRE_CONDITION(min < max);
    std::mt19937                     rng(detail::rand_seed());
    std::uniform_int_distribution<T> dist(min, max);
    return dist(rng);
}

} // namespace core::math
