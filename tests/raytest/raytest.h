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

} // namespace test

// NOLINTBEGIN(*-macro-usage)
#define RG_TEST_EPSILON_FLOAT  0.000001F
#define RG_TEST_EPSILON_DOUBLE 0.000001D

#define S_FWINTS uint8_t, uint16_t, uint32_t, uint64_t
#define U_FWINTS int8_t, int16_t, int32_t, int64_t
#define FWINTS   U_FWINTS, S_FWINTS
#define FWINT_PAIRS                                                            \
    ::test::TypePair<uint8_t, uint8_t>,       /*FORMATTING*/                   \
        ::test::TypePair<uint8_t, uint16_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint8_t, uint32_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint8_t, uint64_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint8_t, int8_t>,    /*FORMATTING*/                   \
        ::test::TypePair<uint8_t, int16_t>,   /*FORMATTING*/                   \
        ::test::TypePair<uint8_t, int32_t>,   /*FORMATTING*/                   \
        ::test::TypePair<uint8_t, int64_t>,   /*FORMATTING*/                   \
        ::test::TypePair<uint16_t, uint8_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint16_t, uint16_t>, /*FORMATTING*/                   \
        ::test::TypePair<uint16_t, uint32_t>, /*FORMATTING*/                   \
        ::test::TypePair<uint16_t, uint64_t>, /*FORMATTING*/                   \
        ::test::TypePair<uint16_t, int8_t>,   /*FORMATTING*/                   \
        ::test::TypePair<uint16_t, int16_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint16_t, int32_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint16_t, int64_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint32_t, uint8_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint32_t, uint16_t>, /*FORMATTING*/                   \
        ::test::TypePair<uint32_t, uint32_t>, /*FORMATTING*/                   \
        ::test::TypePair<uint32_t, uint64_t>, /*FORMATTING*/                   \
        ::test::TypePair<uint32_t, int8_t>,   /*FORMATTING*/                   \
        ::test::TypePair<uint32_t, int16_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint32_t, int32_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint32_t, int64_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint64_t, uint8_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint64_t, uint16_t>, /*FORMATTING*/                   \
        ::test::TypePair<uint64_t, uint32_t>, /*FORMATTING*/                   \
        ::test::TypePair<uint64_t, uint64_t>, /*FORMATTING*/                   \
        ::test::TypePair<uint64_t, int8_t>,   /*FORMATTING*/                   \
        ::test::TypePair<uint64_t, int16_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint64_t, int32_t>,  /*FORMATTING*/                   \
        ::test::TypePair<uint64_t, int64_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int8_t, uint8_t>,    /*FORMATTING*/                   \
        ::test::TypePair<int8_t, uint16_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int8_t, uint32_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int8_t, uint64_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int8_t, int8_t>,     /*FORMATTING*/                   \
        ::test::TypePair<int8_t, int16_t>,    /*FORMATTING*/                   \
        ::test::TypePair<int8_t, int32_t>,    /*FORMATTING*/                   \
        ::test::TypePair<int8_t, int64_t>,    /*FORMATTING*/                   \
        ::test::TypePair<int16_t, uint8_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int16_t, uint16_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int16_t, uint32_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int16_t, uint64_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int16_t, int8_t>,    /*FORMATTING*/                   \
        ::test::TypePair<int16_t, int16_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int16_t, int32_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int16_t, int64_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int32_t, uint8_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int32_t, uint16_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int32_t, uint32_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int32_t, uint64_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int32_t, int8_t>,    /*FORMATTING*/                   \
        ::test::TypePair<int32_t, int16_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int32_t, int32_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int32_t, int64_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int64_t, uint8_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int64_t, uint16_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int64_t, uint32_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int64_t, uint64_t>,  /*FORMATTING*/                   \
        ::test::TypePair<int64_t, int8_t>,    /*FORMATTING*/                   \
        ::test::TypePair<int64_t, int16_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int64_t, int32_t>,   /*FORMATTING*/                   \
        ::test::TypePair<int64_t, int64_t>    /*FORMATTING*/

#define RG_TEST_FLOAT(a, b)                                                    \
    REQUIRE(                                                                   \
        static_cast<double>(a)                                                 \
        == doctest::Approx(static_cast<double>(b))                             \
               .epsilon(static_cast<double>(RG_TEST_EPSILON_FLOAT))            \
    )

#define RG_TEST_DOUBLE(a, b)                                                   \
    REQUIRE(a == doctest::Approx(b).epsilon(RG_TEST_EPSILON_DOUBLE))

#define RG_TEST_SUITE(str)         TEST_SUITE(str)
#define RG_TEST_CASE(str)          TEST_CASE(str)
#define RG_TEST_CASE_TEMPLATE(...) TEST_CASE_TEMPLATE(__VA_ARGS__)
#define RG_SUBCASE(str)            SUBCASE(str)

#define RG_CHECK_THROWS_AS(expr, except) CHECK_THROWS_AS(expr, except)
#define RG_CHECK_NOTHROW(expr)           CHECK_NOTHROW(expr)
#define RG_CHECK_EQ(aval, bval)          CHECK_EQ(aval, bval)

// NOLINTEND(*-macro-usage)

#if defined(RAYGAME_TESTLIB_DOCTEST)
#    include <doctest/doctest.h>
#elif defined(RAYGAME_TESTLIB_GTEST)
#    include <gtest/gtest.h>
#else
#    error "No defined test library"
#endif
