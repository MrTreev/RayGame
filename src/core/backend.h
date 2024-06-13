#pragma once
#include "core/config.h"
RAYGAME_SYSTEM_HEADER

//! Graphical backend
#if defined(RAYGAME_BACKEND_RAYLIB)
#    if !defined(RAYLIB_CPP_NO_MATH)
#        if !defined(RAYMATH_STATIC_INLINE) && !defined(RAYMATH_IMPLEMENTATION)
#            define RAYMATH_STATIC_INLINE
#        endif
#    endif
extern "C" {
#    include <raylib.h>  // IWYU pragma: export
#    include <raymath.h> // IWYU pragma: export
#    include <rlgl.h>    // IWYU pragma: export
}
#    if defined(RAYLIB_VERSION_MAJOR)
#        if RAYLIB_VERSION_MAJOR < 5
#            error "raylib-cpp requires at least raylib 5.0.0"
#        endif
#    else
#        error "raylib not found"
#    endif
#elif defined(RAYGAME_BACKEND_VULKAN)
#    define GLFW_INCLUDE_VULKAN
#    include <GLFW/glfw3.h> // IWYU pragma: export
#elif defined(RAYGAME_BACKEND_SDL)
#    include <SDL3/SDL.h> // IWYU pragma: export

static struct window {
    SDL_Window*   window{nullptr};
    SDL_Renderer* renderer{nullptr};
    bool          should_close{false};
} backend; //NOLINT
#else
#    error "No backend defined"
#endif
