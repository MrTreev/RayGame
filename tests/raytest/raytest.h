#pragma once
#include "gtest/gtest.h"
#include <algorithm>
#include <cstdint>
#include <limits>
#include <vector>

#if defined(__clang__)
#    define RAYTEST_CC_CLANG
#    define RAYTEST_COMPILER CLANG;
#elif defined(__GNUC__)
#    define RAYTEST_CC_GCC
#    define RAYTEST_COMPILER GCC;
#elif defined(__MINGW32__)
#    define RAYTEST_CC_MINGW
#    define RAYTEST_COMPILER MINGW;
#elif defined(_MSC_VER)
#    define RAYTEST_CC_MSC
#    define RAYTEST_COMPILER MSC;
#else
static_assert(false, "Unknown Compiler");
#endif

// NOLINTBEGIN(*-macro-usage)
#if defined(RAYTEST_CC_CLANG)
#    define RAYTEST_PRAGMA_TO_STR(x)            _Pragma(#x)
#    define RAYTEST_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#    define RAYTEST_CLANG_SUPPRESS_WARNING(warnstr)                            \
        RAYTEST_PRAGMA_TO_STR(clang diagnostic ignored warnstr)
#    define RAYTEST_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
#else
#    define RAYTEST_CLANG_SUPPRESS_WARNING_PUSH
#    define RAYTEST_CLANG_SUPPRESS_WARNING(warnstr)
#    define RAYTEST_CLANG_SUPPRESS_WARNING_POP
#endif
#if defined(RAYTEST_CC_GCC)
#    define RAYTEST_PRAGMA_TO_STR(x)          _Pragma(#x)
#    define RAYTEST_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#    define RAYTEST_GCC_SUPPRESS_WARNING(warnstr)                              \
        RAYTEST_PRAGMA_TO_STR(GCC diagnostic ignored warnstr)
#    define RAYTEST_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#else
#    define RAYTEST_GCC_SUPPRESS_WARNING_PUSH
#    define RAYTEST_GCC_SUPPRESS_WARNING(warnstr)
#    define RAYTEST_GCC_SUPPRESS_WARNING_POP
#endif
#if defined(RAYTEST_CC_MSC)
#    define RAYTEST_MSC_SUPPRESS_WARNING_PUSH     __pragma(warning(push))
#    define RAYTEST_MSC_SUPPRESS_WARNING(warnstr) __pragma(warning(disable : w))
#    define RAYTEST_MSC_SUPPRESS_WARNING_POP      __pragma(warning(pop))
#else
#    define RAYTEST_MSC_SUPPRESS_WARNING_PUSH
#    define RAYTEST_MSC_SUPPRESS_WARNING(warnstr)
#    define RAYTEST_MSC_SUPPRESS_WARNING_POP
#endif
// NOLINTEND(*-macro-usage)

RAYTEST_CLANG_SUPPRESS_WARNING_PUSH
RAYTEST_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
#include <gtest/gtest.h> // IWYU pragma: export
RAYTEST_CLANG_SUPPRESS_WARNING_POP

// NOLINTBEGIN(*-macro-usage)
#define RG_TYPED_TEST_SUITE(test_suite_name, test_name)                        \
    TYPED_TEST_SUITE(test_suite_name, test_name)
#define RG_TYPED_TEST(test_suite_name, test_name)                              \
    RAYTEST_CLANG_SUPPRESS_WARNING_PUSH                                        \
    RAYTEST_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")                    \
    TYPED_TEST(test_suite_name, test_name)                                     \
    RAYTEST_CLANG_SUPPRESS_WARNING_POP
#define RG_TEST(test_suite_name, test_name)                                    \
    RAYTEST_CLANG_SUPPRESS_WARNING_PUSH                                        \
    RAYTEST_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")                    \
    TEST(test_suite_name, test_name)                                           \
    RAYTEST_CLANG_SUPPRESS_WARNING_POP

#define RG_TEST_FLOAT(a, b)          EXPECT_FLOAT_EQ((a), (b))
#define RG_TEST_DOUBLE(a, b)         EXPECT_DOUBLE_EQ((a), (b))
#define RG_CHECK_THROW(expr, except) EXPECT_THROW((expr), except)
#define RG_CHECK_NO_THROW(expr)      EXPECT_NO_THROW((expr))
#define RG_CHECK_TRUE(aval)          EXPECT_TRUE((aval))
#define RG_CHECK_FALSE(aval)         EXPECT_FALSE((aval))
#define RG_CHECK_EQ(aval, bval)      EXPECT_EQ((aval), (bval))
#define RG_CHECK_GT(aval, bval)      EXPECT_GT((aval), (bval))
#define RG_CHECK_GE(aval, bval)      EXPECT_GE((aval), (bval))
#define RG_CHECK_LT(aval, bval)      EXPECT_LT((aval), (bval))
#define RG_CHECK_LE(aval, bval)      EXPECT_LE((aval), (bval))
#define RG_SUBCASE(str)

// NOLINTEND(*-macro-usage)

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
    return std::all_of(arr.begin(), arr.end(), [&aval = arr[0]](T bval) {
        return aval == bval;
    });
}

template<typename T, size_t N>
constexpr bool all_same(std::array<T, N> arr) {
    return std::all_of(arr.begin(), arr.end(), [&aval = arr[0]](T bval) {
        return aval == bval;
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

namespace types {
using Integral = testing::Types<
    uint8_t,
    uint16_t,
    uint32_t,
    uint64_t,
    int8_t,
    int16_t,
    int32_t,
    int64_t>;

using IntegralPairs = ::testing::Types<
    ::test::TypePair<uint8_t, uint8_t>,
    ::test::TypePair<uint8_t, uint16_t>,
    ::test::TypePair<uint8_t, uint32_t>,
    ::test::TypePair<uint8_t, uint64_t>,
    ::test::TypePair<uint8_t, int8_t>,
    ::test::TypePair<uint8_t, int16_t>,
    ::test::TypePair<uint8_t, int32_t>,
    ::test::TypePair<uint8_t, int64_t>,
    ::test::TypePair<uint16_t, uint8_t>,
    ::test::TypePair<uint16_t, uint16_t>,
    ::test::TypePair<uint16_t, uint32_t>,
    ::test::TypePair<uint16_t, uint64_t>,
    ::test::TypePair<uint16_t, int8_t>,
    ::test::TypePair<uint16_t, int16_t>,
    ::test::TypePair<uint16_t, int32_t>,
    ::test::TypePair<uint16_t, int64_t>,
    ::test::TypePair<uint32_t, uint8_t>,
    ::test::TypePair<uint32_t, uint16_t>,
    ::test::TypePair<uint32_t, uint32_t>,
    ::test::TypePair<uint32_t, uint64_t>,
    ::test::TypePair<uint32_t, int8_t>,
    ::test::TypePair<uint32_t, int16_t>,
    ::test::TypePair<uint32_t, int32_t>,
    ::test::TypePair<uint32_t, int64_t>,
    ::test::TypePair<uint64_t, uint8_t>,
    ::test::TypePair<uint64_t, uint16_t>,
    ::test::TypePair<uint64_t, uint32_t>,
    ::test::TypePair<uint64_t, uint64_t>,
    ::test::TypePair<uint64_t, int8_t>,
    ::test::TypePair<uint64_t, int16_t>,
    ::test::TypePair<uint64_t, int32_t>,
    ::test::TypePair<uint64_t, int64_t>,
    ::test::TypePair<int8_t, uint8_t>,
    ::test::TypePair<int8_t, uint16_t>,
    ::test::TypePair<int8_t, uint32_t>,
    ::test::TypePair<int8_t, uint64_t>,
    ::test::TypePair<int8_t, int8_t>,
    ::test::TypePair<int8_t, int16_t>,
    ::test::TypePair<int8_t, int32_t>,
    ::test::TypePair<int8_t, int64_t>,
    ::test::TypePair<int16_t, uint8_t>,
    ::test::TypePair<int16_t, uint16_t>,
    ::test::TypePair<int16_t, uint32_t>,
    ::test::TypePair<int16_t, uint64_t>,
    ::test::TypePair<int16_t, int8_t>,
    ::test::TypePair<int16_t, int16_t>,
    ::test::TypePair<int16_t, int32_t>,
    ::test::TypePair<int16_t, int64_t>,
    ::test::TypePair<int32_t, uint8_t>,
    ::test::TypePair<int32_t, uint16_t>,
    ::test::TypePair<int32_t, uint32_t>,
    ::test::TypePair<int32_t, uint64_t>,
    ::test::TypePair<int32_t, int8_t>,
    ::test::TypePair<int32_t, int16_t>,
    ::test::TypePair<int32_t, int32_t>,
    ::test::TypePair<int32_t, int64_t>,
    ::test::TypePair<int64_t, uint8_t>,
    ::test::TypePair<int64_t, uint16_t>,
    ::test::TypePair<int64_t, uint32_t>,
    ::test::TypePair<int64_t, uint64_t>,
    ::test::TypePair<int64_t, int8_t>,
    ::test::TypePair<int64_t, int16_t>,
    ::test::TypePair<int64_t, int32_t>,
    ::test::TypePair<int64_t, int64_t>>;

using All = ::testing::Types<void>;

} // namespace types
} // namespace test
