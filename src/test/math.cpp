#include "core/math.h"
#include <algorithm>
#include <fuzztest/fuzztest.h>
#include <gtest/gtest.h>
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

template<typename T>
class SignedMathTest: public testing::Test {};

template<typename T>
class UnsignedMathTest: public testing::Test {};

template<typename T>
class AllMathTest: public testing::Test {};

using SignedInts   = ::testing::Types<S_FWINTS>;
using UnsignedInts = ::testing::Types<U_FWINTS>;
using AllInts      = ::testing::Types<FWINTS>;
TYPED_TEST_SUITE(SignedMathTest, SignedInts);
TYPED_TEST_SUITE(UnsignedMathTest, UnsignedInts);
TYPED_TEST_SUITE(AllMathTest, AllInts);

TYPED_TEST(AllMathTest, RandNArray) {
    std::array<TypeParam, test_len> rands =
        core::math::rand_n<TypeParam, test_len>();
    EXPECT_EQ(rands.size(), test_len);
    EXPECT_FALSE(all_same(rands));
    std::array<TypeParam, test_len> rand_01 =
        core::math::rand_n<TypeParam, test_len>(0, 1);
    EXPECT_EQ(rand_01.size(), test_len);
    EXPECT_FALSE(all_same(rand_01));
    for (const auto& val: rand_01) {
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 1);
    }
}

TYPED_TEST(AllMathTest, RandNVector) {
    std::vector<TypeParam> rands = core::math::rand_n<TypeParam>(test_len);
    EXPECT_EQ(rands.size(), test_len);
    EXPECT_FALSE(all_same(rands));
    std::vector<TypeParam> rand_01 =
        core::math::rand_n<TypeParam>(0, 1, test_len);
    EXPECT_EQ(rand_01.size(), test_len);
    EXPECT_FALSE(all_same(rand_01));
    for (const auto& val: rand_01) {
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 1);
    }
}

TYPED_TEST(AllMathTest, NumericCast) {
    EXPECT_NO_THROW(core::math::numeric_cast<TypeParam>(max<TypeParam>()));
    EXPECT_NO_THROW(core::math::numeric_cast<TypeParam>(min<TypeParam>()));
    EXPECT_NO_THROW(core::math::numeric_cast<TypeParam>(lowest<TypeParam>()));
    const auto test_vec = core::math::rand_n<TypeParam>(
        min<TypeParam>(),
        max<TypeParam>(),
        test_len
    );
    for (const TypeParam& num: test_vec) {
        EXPECT_NO_THROW(core::math::numeric_cast<TypeParam>(num));
    }
}

TYPED_TEST(SignedMathTest, NumericCast) {
    EXPECT_THROW(
        core::math::numeric_cast<TypeParam>(max<TypeParam>() + 1),
        Condition
    );
    EXPECT_THROW(
        core::math::numeric_cast<TypeParam>(min<TypeParam>() - 1),
        Condition
    );
}

TYPED_TEST(UnsignedMathTest, NumericCast) {
    EXPECT_THROW(
        core::math::numeric_cast<TypeParam>(max<TypeParam>() + 1),
        Condition
    );
    EXPECT_THROW(
        core::math::numeric_cast<TypeParam>(min<TypeParam>() - 1),
        Condition
    );
}
