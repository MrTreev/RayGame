#pragma once
#include "doctest/doctest.h" // IWYU pragma: export
#include "core/test/test.h"       // IWYU pragma: export
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
