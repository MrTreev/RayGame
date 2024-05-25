#pragma once

#include "core/include/config.h"

#if defined(RAYGAME_CC_CLANG)
#    pragma clang system_header
#elif defined(RAYGAME_CC_GCC)
#    pragma GCC system_header
#endif

#include <cstdint> // IWYU pragma: export

using int16_t  = std::int16_t;
using int32_t  = std::int32_t;
using int64_t  = std::int64_t;
using int8_t   = std::int8_t;
using uint16_t = std::uint16_t;
using uint32_t = std::uint32_t;
using uint64_t = std::uint64_t;
using uint8_t  = std::uint8_t;

using intmax_t  = std::intmax_t;
using intptr_t  = std::intptr_t;
using uintmax_t = std::uintmax_t;
using uintptr_t = std::uintptr_t;
