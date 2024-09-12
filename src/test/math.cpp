#include "core/math.h"
#include <algorithm>
#include <doctest/doctest.h>
#include <limits>

#define S_FWINTS uint8_t, uint16_t, uint32_t
#define U_FWINTS int8_t, int16_t, int32_t
#define FWINTS   U_FWINTS, S_FWINTS
using core::exception::Condition;

namespace {
template<
    typename T,
    typename M =
        std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>>
constexpr inline M lowest() {
    return std::numeric_limits<T>::lowest();
}

template<
    typename T,
    typename M =
        std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>>
constexpr inline M min() {
    return std::numeric_limits<T>::min();
}

template<
    typename T,
    typename M =
        std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>>
constexpr inline M max() {
    return std::numeric_limits<T>::max();
}

template<typename T>
inline constexpr bool all_same(std::vector<T> arr) {
    return std::all_of(arr.begin(), arr.end(), [&a = arr[0]](T b) {
        return a == b;
    });
}

template<typename T, size_t N>
inline constexpr bool all_same(std::array<T, N> arr) {
    return std::all_of(arr.begin(), arr.end(), [&a = arr[0]](T b) {
        return a == b;
    });
}
} // namespace

constexpr size_t test_len = 16;

TEST_SUITE("rand_n") {
    TEST_CASE_TEMPLATE("std::array", T, FWINTS) {
        std::array<T, test_len> rands = core::math::rand_n<T, test_len>();
        CHECK_EQ(rands.size(), test_len);
        CHECK_FALSE(all_same(rands));
        std::array<T, test_len> rand_01 = core::math::rand_n<T, test_len>(0, 1);
        CHECK_EQ(rand_01.size(), test_len);
        CHECK_FALSE(all_same(rand_01));
        for (const auto& val: rand_01) {
            CHECK_GE(val, 0);
            CHECK_LE(val, 1);
        }
    }
    TEST_CASE_TEMPLATE("std::vector", T, FWINTS) {
        std::vector<T> rands = core::math::rand_n<T>(test_len);
        CHECK_EQ(rands.size(), test_len);
        CHECK_FALSE(all_same(rands));
        std::vector<T> rand_01 = core::math::rand_n<T>(0, 1, test_len);
        CHECK_EQ(rand_01.size(), test_len);
        CHECK_FALSE(all_same(rand_01));
        for (const auto& val: rand_01) {
            CHECK_GE(val, 0);
            CHECK_LE(val, 1);
        }
    }
}

TEST_SUITE("numeric_cast") {
    TEST_CASE_TEMPLATE("In-range does not throw", T, FWINTS) {
        CHECK_NOTHROW(core::math::numeric_cast<T>(max<T>()));
        CHECK_NOTHROW(core::math::numeric_cast<T>(min<T>()));
        CHECK_NOTHROW(core::math::numeric_cast<T>(lowest<T>()));
        const auto test_vec =
            core::math::rand_n<T>(min<T>(), max<T>(), test_len);
        for (const T& num: test_vec) {
            CHECK_NOTHROW(core::math::numeric_cast<T>(num));
        }
    }
    TEST_CASE_TEMPLATE("Signed out-of-range throws", T, S_FWINTS) {
        CHECK_THROWS_AS(core::math::numeric_cast<T>(max<T>() + 1), Condition);
        CHECK_THROWS_AS(core::math::numeric_cast<T>(min<T>() - 1), Condition);
    }
    TEST_CASE_TEMPLATE("Unsigned out-of-range throws", T, U_FWINTS) {
        CHECK_THROWS_AS(core::math::numeric_cast<T>(max<T>() + 1), Condition);
        CHECK_THROWS_AS(core::math::numeric_cast<T>(min<T>() - 1), Condition);
    }
}

TEST_SUITE("safe_add") {
    TEST_CASE_TEMPLATE("In-range does not throw", T, FWINTS) {
        for (size_t i = 0; i > 100; ++i) {
            const T a = core::math::rand<T>();
            const T b = core::math::rand<T>();
            if (a + b > max<T>()) {
                CHECK_THROWS_AS(core::math::safe_add<T>(a, b), Condition);
            } else if (a + b < min<T>()) {
                CHECK_THROWS_AS(core::math::safe_add<T>(a, b), Condition);
            } else {
                CHECK_NOTHROW(core::math::safe_add<T>(a, b));
            }
        }
    }
}
