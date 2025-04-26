#pragma once
// NOLINTBEGIN(*-macro-usage)
#include "raytest/test.h" // IWYU pragma: export
#define RG_TEST_EPSILON_FLOAT  0.000001F
#define RG_TEST_EPSILON_DOUBLE 0.000001D

#define S_FWINTS uint8_t, uint16_t, uint32_t, uint64_t
#define U_FWINTS int8_t, int16_t, int32_t, int64_t
#define FWINTS   U_FWINTS, S_FWINTS
#define FWINT_PAIRS                                                            \
    ::test::TypePair<uint8_t, uint8_t>, ::test::TypePair<uint8_t, uint16_t>,   \
        ::test::TypePair<uint8_t, uint32_t>,                                   \
        ::test::TypePair<uint8_t, uint64_t>,                                   \
        ::test::TypePair<uint8_t, int8_t>, ::test::TypePair<uint8_t, int16_t>, \
        ::test::TypePair<uint8_t, int32_t>,                                    \
        ::test::TypePair<uint8_t, int64_t>,                                    \
        ::test::TypePair<uint16_t, uint8_t>,                                   \
        ::test::TypePair<uint16_t, uint16_t>,                                  \
        ::test::TypePair<uint16_t, uint32_t>,                                  \
        ::test::TypePair<uint16_t, uint64_t>,                                  \
        ::test::TypePair<uint16_t, int8_t>,                                    \
        ::test::TypePair<uint16_t, int16_t>,                                   \
        ::test::TypePair<uint16_t, int32_t>,                                   \
        ::test::TypePair<uint16_t, int64_t>,                                   \
        ::test::TypePair<uint32_t, uint8_t>,                                   \
        ::test::TypePair<uint32_t, uint16_t>,                                  \
        ::test::TypePair<uint32_t, uint32_t>,                                  \
        ::test::TypePair<uint32_t, uint64_t>,                                  \
        ::test::TypePair<uint32_t, int8_t>,                                    \
        ::test::TypePair<uint32_t, int16_t>,                                   \
        ::test::TypePair<uint32_t, int32_t>,                                   \
        ::test::TypePair<uint32_t, int64_t>,                                   \
        ::test::TypePair<uint64_t, uint8_t>,                                   \
        ::test::TypePair<uint64_t, uint16_t>,                                  \
        ::test::TypePair<uint64_t, uint32_t>,                                  \
        ::test::TypePair<uint64_t, uint64_t>,                                  \
        ::test::TypePair<uint64_t, int8_t>,                                    \
        ::test::TypePair<uint64_t, int16_t>,                                   \
        ::test::TypePair<uint64_t, int32_t>,                                   \
        ::test::TypePair<uint64_t, int64_t>,                                   \
        ::test::TypePair<int8_t, uint8_t>, ::test::TypePair<int8_t, uint16_t>, \
        ::test::TypePair<int8_t, uint32_t>,                                    \
        ::test::TypePair<int8_t, uint64_t>, ::test::TypePair<int8_t, int8_t>,  \
        ::test::TypePair<int8_t, int16_t>, ::test::TypePair<int8_t, int32_t>,  \
        ::test::TypePair<int8_t, int64_t>, ::test::TypePair<int16_t, uint8_t>, \
        ::test::TypePair<int16_t, uint16_t>,                                   \
        ::test::TypePair<int16_t, uint32_t>,                                   \
        ::test::TypePair<int16_t, uint64_t>,                                   \
        ::test::TypePair<int16_t, int8_t>, ::test::TypePair<int16_t, int16_t>, \
        ::test::TypePair<int16_t, int32_t>,                                    \
        ::test::TypePair<int16_t, int64_t>,                                    \
        ::test::TypePair<int32_t, uint8_t>,                                    \
        ::test::TypePair<int32_t, uint16_t>,                                   \
        ::test::TypePair<int32_t, uint32_t>,                                   \
        ::test::TypePair<int32_t, uint64_t>,                                   \
        ::test::TypePair<int32_t, int8_t>, ::test::TypePair<int32_t, int16_t>, \
        ::test::TypePair<int32_t, int32_t>,                                    \
        ::test::TypePair<int32_t, int64_t>,                                    \
        ::test::TypePair<int64_t, uint8_t>,                                    \
        ::test::TypePair<int64_t, uint16_t>,                                   \
        ::test::TypePair<int64_t, uint32_t>,                                   \
        ::test::TypePair<int64_t, uint64_t>,                                   \
        ::test::TypePair<int64_t, int8_t>, ::test::TypePair<int64_t, int16_t>, \
        ::test::TypePair<int64_t, int32_t>, ::test::TypePair<int64_t, int64_t>

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

#include "doctest/doctest.h" // IWYU pragma: export
