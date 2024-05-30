#pragma once
#include "core/config.h"

RAYGAME_SYSTEM_HEADER

#if !defined(RAYLIB_CPP_NO_MATH)
#    if !defined(RAYMATH_STATIC_INLINE) && !defined(RAYMATH_IMPLEMENTATION)
#        define RAYMATH_STATIC_INLINE
#    endif
#endif
extern "C" {
#include <raylib.h>  // IWYU pragma: export
#include <raymath.h> // IWYU pragma: export
}
#if defined(RAYLIB_VERSION_MAJOR)
#    if RAYLIB_VERSION_MAJOR < 5
#        error "raylib-cpp requires at least raylib 5.0.0"
#    endif
#else
#    error "raylib not found"
#endif
