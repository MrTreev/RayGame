#pragma once
#include "core/condition.h"
#include "core/debug.h"
#include "core/exception.h"
#include "core/types.h"
#include <cassert>
#include <concepts>
#include <limits>
#include <random>
#include <type_traits>
#include <utility>

namespace core::math {

namespace constants {
constexpr float pi      = 3.14159265358979323846F;
constexpr float deg2rad = (pi / 180.0F);
constexpr float rad2deg = (180.0F / pi);
constexpr float epsilon = 0.000001F;
} // namespace constants

inline constexpr core::rad_t deg2rad(core::deg_t deg) {
    return deg * constants::deg2rad;
};

inline constexpr core::deg_t rad2deg(core::rad_t rad) {
    return rad * constants::rad2deg;
};

template<typename Out_T, typename A_T, typename B_T>
inline constexpr Out_T safe_add(A_T a, B_T b) {
    if constexpr (std::is_unsigned_v<A_T> && std::is_unsigned_v<B_T>) {
        const uintmax_t ai  = static_cast<uintmax_t>(a);
        const uintmax_t bi  = static_cast<uintmax_t>(b);
        const uintmax_t res = ai + bi;
        assert((res > a) && (res > b));
        return numeric_cast<Out_T>(a + b);
    }
}

template<typename Out_T, typename In_T>
requires(std::integral<Out_T> && std::integral<In_T>)
inline constexpr Out_T numeric_cast(In_T input) {
    if (std::in_range<Out_T>(input)) {
        return static_cast<Out_T>(input);
    } else {
        RG_THROW_CONDITION(
            "Input of type '{}' is above the max for output type '{}'",
            core::debug::type_name(input),
            input
        );
    }
}

//! Returns an array of N random values in a range
/*!
 * @param min minimum random value
 * @param max maximum random value
 */
template<typename T, size_t N>
requires std::is_integral_v<T> && std::is_trivial_v<T>
inline constexpr std::array<T, N> rand_n(T min, T max) {
    RG_PRE_CONDITION(min < max);
    std::random_device               dev;
    std::mt19937                     rng(dev());
    std::uniform_int_distribution<T> dist(min, max);
    std::array<T, N>                 results;
    for (T& res: results) {
        res = dist(rng);
    }
    return results;
}

template<typename T, size_t N>
requires std::is_integral_v<T> && std::is_trivial_v<T>
inline constexpr std::array<T, N> rand_n() {
    return rand_n<T, N>(
        std::numeric_limits<T>::min(),
        std::numeric_limits<T>::max()
    );
};

template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
inline constexpr std::vector<T> rand_n(T min, T max, size_t amount) {
    RG_PRE_CONDITION(min < max);
    std::random_device               dev;
    std::mt19937                     rng(dev());
    std::uniform_int_distribution<T> dist(min, max);
    std::vector<T>                   results;
    results.reserve(amount);
    while (results.size() < amount) {
        results.push_back(dist(rng));
    }
    return results;
}

template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
inline constexpr std::vector<T> rand_n(size_t amount) {
    return rand_n<T>(
        std::numeric_limits<T>::min(),
        std::numeric_limits<T>::max(),
        amount
    );
}

template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
inline constexpr T rand(T min, T max) {
    RG_PRE_CONDITION(min < max);
    std::random_device               dev;
    std::mt19937                     rng(dev());
    std::uniform_int_distribution<T> dist(min, max);
    return dist(rng);
}

template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
inline constexpr T rand() {
    return rand(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

} // namespace core::math
