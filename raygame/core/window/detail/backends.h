#pragma once
#include "raygame/core/config.h" // IWYU pragma: export
#if !defined(RAYGAME_GUI_BACKEND_RAYLIB)
#    define RAYGAME_GUI_BACKEND_RAYLIB
#endif
#if defined(RAYGAME_OS_LINUX) || defined(RAYGAME_OS_BSD) || defined(RAYGAME_OS_HURD)
#    if !defined(RAYGAME_GUI_BACKEND_WAYLAND)
#        define RAYGAME_GUI_BACKEND_WAYLAND
#    endif
#elif defined(RAYGAME_OS_WIN32) || defined(RAYGAME_OS_WIN64)
#    if !defined(RAYGAME_GUI_BACKEND_DWM)
#        define RAYGAME_GUI_BACKEND_DWM
#    endif
#elif defined(RAYGAME_OS_MAC)
#    if !defined(RAYGAME_GUI_BACKEND_COCOA)
#        define RAYGAME_GUI_BACKEND_COCOA
#    endif
#endif

namespace core::config {
//! Window Backends
enum class GuiBackend : uint8_t {
    COCOA,
    DWM,
    WAYLAND,
    RAYLIB,
};
} // namespace core::config
