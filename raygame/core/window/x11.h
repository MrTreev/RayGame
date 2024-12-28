#pragma once
#include "raygame/core/window/window.h"
RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
#include <X11/Xlib.h>
RAYGAME_CLANG_SUPPRESS_WARNING_POP

namespace core::window {
class X11Window final: public Window {
public:
    explicit X11Window(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    ~X11Window() final;
    X11Window(X11Window&&)                 = default;
    X11Window& operator=(X11Window&&)      = default;
    X11Window(const X11Window&)            = delete;
    X11Window& operator=(const X11Window&) = delete;

    void set_style(WindowStyle style);
    void render_frame() final;

private:
    ::Display* m_display = nullptr;
    int        m_screen  = 0;
    ::XEvent   m_event{};
    ::Window   m_window{};
};

} // namespace core::window
