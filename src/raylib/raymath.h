#pragma once

// IWYU pragma: always_keep

#if defined(__clang__)
#    pragma clang system_header
#endif

extern "C" {
#if !defined(RAYLIB_CPP_NO_MATH)
#    if !defined(RAYMATH_STATIC_INLINE) && !defined(RAYMATH_IMPLEMENTATION)
#        define RAYMATH_STATIC_INLINE
#    endif
#    include <raymath.h>
#endif
}
