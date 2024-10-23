#pragma once
#if defined(RAYGAME_ENABLE_TESTS)
#    define DOCTEST_CONFIG_IMPLEMENT
#    include "test/test.h"       // IWYU pragma: export
#    include <doctest/doctest.h> // IWYU pragma: export
#    define S_FWINTS uint8_t, uint16_t, uint32_t
#    define U_FWINTS int8_t, int16_t, int32_t
#    define FWINTS   U_FWINTS, S_FWINTS
#endif
