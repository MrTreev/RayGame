#pragma once
#include "raygame/core/config/operating_system.h"
#if defined(RAYGAME_OS_LINUX) || defined(RAYGAME_OS_BSD)                       \
    || defined(RAYGAME_OS_HURD)
#    if !defined(RAYGAME_GUI_BACKEND_WAYLAND)
#        define RAYGAME_GUI_BACKEND_WAYLAND
#    endif
#    if !defined(RAYGAME_GUI_BACKEND_X11)
#        define RAYGAME_GUI_BACKEND_X11
#    endif
#elif defined(RAYGAME_OS_WIN32) || defined(RAYGAME_OS_WIN64)
#    if !defined(RAYGAME_GUI_BACKEND_DWM)
#        define RAYGAME_GUI_BACKEND_DWM
#    endif
#elif defined(RAYGAME_OS_TEMPLEOS)
#    if !defined(RAYGAME_GUI_BACKEND_TEMPLE)
#        define RAYGAME_GUI_BACKEND_TEMPLE
#    endif
#elif defined(RAYGAME_OS_MAC)
#    if !defined(RAYGAME_GUI_BACKEND_COCOA)
#        define RAYGAME_GUI_BACKEND_COCOA
#    endif
#endif

namespace core::config::detail {
consteval bool backend_cocoa() {
#if defined(RAYGAME_GUI_BACKEND_COCOA)
    return true;
#else
    return false;
#endif
}

consteval bool backend_dwm() {
#if defined(RAYGAME_GUI_BACKEND_DWM)
    return true;
#else
    return false;
#endif
}

consteval bool backend_temple() {
#if defined(RAYGAME_GUI_BACKEND_TEMPLE)
    return true;
#else
    return false;
#endif
}

consteval bool backend_wayland() {
#if defined(RAYGAME_GUI_BACKEND_WAYLAND)
    return true;
#else
    return false;
#endif
}

consteval bool backend_x11() {
#if defined(RAYGAME_GUI_BACKEND_X11)
    return true;
#else
    return false;
#endif
}

} // namespace core::config::detail
