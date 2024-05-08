#pragma once

// IWYU pragma: always_keep

#if defined(__clang__)
#    pragma clang system_header
#endif

extern "C" {
#include <raylib.h>
}

#if defined(RAYLIB_VERSION_MAJOR)
#    if RAYLIB_VERSION_MAJOR < 5
#        error "raylib-cpp requires at least raylib 5.0.0"
#    endif
#else
#    error "raylib not found"
#endif
