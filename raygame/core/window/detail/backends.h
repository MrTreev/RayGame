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
    TEMPLE,
    WAYLAND,
    IMGUI,
    RAYLIB,
};

class EnabledBackends {
public:
    static consteval bool cocoa() {
#if defined(RAYGAME_GUI_BACKEND_COCOA)
        return true;
#else
        return false;
#endif
    }

    static consteval bool dwm() {
#if defined(RAYGAME_GUI_BACKEND_DWM)
        return true;
#else
        return false;
#endif
    }

    static consteval bool wayland() {
#if defined(RAYGAME_GUI_BACKEND_WAYLAND)
        return true;
#else
        return false;
#endif
    }

    static consteval bool raylib() {
#if defined(RAYGAME_GUI_BACKEND_RAYLIB)
        return true;
#else
        return false;
#endif
    }
};
} // namespace core::config

#if defined(RAYGAME_GUI_BACKEND_COCOA)
#    define RAYGAME_RETURN_COCOA
#else
#    define RAYGAME_RETURN_COCOA [[noreturn]]
#endif

#if defined(RAYGAME_GUI_BACKEND_DWM)
#    define RAYGAME_RETURN_DWM
#else
#    define RAYGAME_RETURN_DWM [[noreturn]]
#endif

#if defined(RAYGAME_GUI_BACKEND_WAYLAND)
#    define RAYGAME_RETURN_WAYLAND
#else
#    define RAYGAME_RETURN_WAYLAND [[noreturn]]
#endif

#if defined(RAYGAME_GUI_BACKEND_IMGUI)
#    define RAYGAME_RETURN_IMGUI
#else
#    define RAYGAME_RETURN_IMGUI [[noreturn]]
#endif

#if defined(RAYGAME_GUI_BACKEND_RAYLIB)
#    define RAYGAME_RETURN_RAYLIB
#else
#    define RAYGAME_RETURN_RAYLIB [[noreturn]]
#endif
