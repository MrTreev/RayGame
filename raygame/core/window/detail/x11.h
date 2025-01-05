#pragma once
#include "raygame/core/window/window.h"
#if defined(RAYGAME_GUI_BACKEND_X11)
RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
#    include <X11/Xlib.h>
RAYGAME_CLANG_SUPPRESS_WARNING_POP
#endif

namespace core::window::detail {
class X11WindowImpl final: public WindowImpl {
public:
    explicit X11WindowImpl(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    X11WindowImpl(const X11WindowImpl&)           = delete;
    X11WindowImpl operator=(const X11WindowImpl&) = delete;
    X11WindowImpl(X11WindowImpl&&)                = default;
    X11WindowImpl& operator=(X11WindowImpl&&)     = default;
    ~X11WindowImpl() final;

    void draw(const drawing::Image& image) final;

    void restyle(WindowStyle style) final;

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;

private:
#if defined(RAYGAME_GUI_BACKEND_X11)
    ::Display* m_display = nullptr;
    int        m_screen  = 0;
    ::XEvent   m_event{};
    ::Window   m_window{};
#endif
};
} // namespace core::window::detail
