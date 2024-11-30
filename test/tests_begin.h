#pragma once
#include "doctest/doctest.h" // IWYU pragma: export
#include "test/test.h"       // IWYU pragma: export

#define S_FWINTS uint8_t, uint16_t, uint32_t
#define U_FWINTS int8_t, int16_t, int32_t
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
