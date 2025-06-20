#pragma once
#include "raygame/core/window/detail/backends.h" // IWYU pragma: keep
#include "raygame/core/window/window.h"
#if defined(RAYGAME_GUI_BACKEND_X11)
RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
#    include <X11/Xlib.h>
RAYGAME_CLANG_SUPPRESS_WARNING_POP
#else
class Display;

class XEvent {};

class Window {};
#endif

namespace core::window::detail {
class X11WindowImpl final: public WindowImpl {
public:
    RAYGAME_RETURN_X11
    X11WindowImpl(Vec2<size_t> size, std::string title, WindowStyle style);
    X11WindowImpl(const X11WindowImpl&)           = delete;
    X11WindowImpl operator=(const X11WindowImpl&) = delete;
    X11WindowImpl(X11WindowImpl&&)                = default;
    X11WindowImpl& operator=(X11WindowImpl&&)     = default;
    ~X11WindowImpl() final;

    void draw(const drawing::ImageView& image) final;

    void restyle(WindowStyle style) final;

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;

private:
    ::Display* m_display = nullptr;
    int        m_screen  = 0;
    ::XEvent   m_event{};
    ::Window   m_window{};
};
} // namespace core::window::detail
