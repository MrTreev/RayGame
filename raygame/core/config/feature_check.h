#pragma once

// clang-format off
#define RAYGAME_CPP_00 199711L
#define RAYGAME_CPP_11 201103L
#define RAYGAME_CPP_14 201402L
#define RAYGAME_CPP_17 201703L
#define RAYGAME_CPP_20 202002L
#define RAYGAME_CPP_23 202302L
// clang-format on

#if !defined(RAYGAME_MIN_CPP_VERSION)
#    define RAYGAME_MIN_CPP_VERSION RAYGAME_CPP_23
#endif

#if RAYGAME_MIN_CPP_VERSION <= 0
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_00
#    define RAYGAME_CPP_STR "C++11"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_11
#    define RAYGAME_CPP_STR "C++11"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_14
#    define RAYGAME_CPP_STR "C++14"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_17
#    define RAYGAME_CPP_STR "C++17"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_20
#    define RAYGAME_CPP_STR "C++20"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_23
#    define RAYGAME_CPP_STR "C++23"
#endif

#if (__cplusplus < RAYGAME_MIN_CPP_VERSION)
#    include "raygame/core/config/conditional.h"
#    include "raygame/core/config/stringify.h"
static_assert(
    false,
    "This game's code uses features from the " RAYGAME_CPP_STR " standard"
);
#endif

#undef RAYGAME_CPP_00
#undef RAYGAME_CPP_11
#undef RAYGAME_CPP_14
#undef RAYGAME_CPP_17
#undef RAYGAME_CPP_20
#undef RAYGAME_CPP_23
#undef RAYGAME_CPP_STR
#undef RAYGAME_MIN_CPP_VERSION
