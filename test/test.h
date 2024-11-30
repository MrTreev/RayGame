#pragma once
#include <algorithm>
#include <cstdint>
#include <limits>
#include <vector>

namespace test {
template<
    typename T,
    typename M =
        std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>>
constexpr M lowest() {
    return std::numeric_limits<T>::lowest();
}

template<
    typename T,
    typename M =
        std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>>
constexpr M min() {
    return std::numeric_limits<T>::lowest();
}

template<
    typename T,
    typename M =
        std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>>
constexpr M max() {
    return std::numeric_limits<T>::max();
}

template<typename T>
constexpr bool all_same(std::vector<T> arr) {
    return std::all_of(arr.begin(), arr.end(), [&a = arr[0]](T b) {
        return a == b;
    });
}

template<typename T, size_t N>
constexpr bool all_same(std::array<T, N> arr) {
    return std::all_of(arr.begin(), arr.end(), [&a = arr[0]](T b) {
        return a == b;
    });
}

template<typename first, typename second>
struct TypePair {
    using A = first;
    using B = second;
};

template<typename first, typename second, typename third>
struct TypeTriple {
    using A = first;
    using B = second;
    using C = third;
};

} // namespace test
