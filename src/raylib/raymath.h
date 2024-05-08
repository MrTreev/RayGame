#pragma once

#if defined(__clang__)
#    pragma clang system_header
#endif

extern "C" {
#if !defined(RAYLIB_CPP_NO_MATH)
#    if !defined(RAYMATH_STATIC_INLINE)
#        define RAYMATH_STATIC_INLINE
#    endif
#    if defined(__GNUC__)
#        pragma GCC diagnostic push
#        pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#    endif
#    include "raymath.h" // NOLINT
#    if defined(__GNUC__)
#        pragma GCC diagnostic pop
#    endif
#endif
}
