#pragma once
#include "raygame/core/config.h"
#include "raygame/core/drawing/image.h"
#include <string>

namespace core::window {
//! Window display styles
enum class WindowStyle : uint8_t {
    Windowed,           //!< Windowed mode (resizable)
    WindowedFullscreen, //!< Windowed mode with no decorations (resizable)
    Fullscreen,         //!< Fullscreen mode
};

static constexpr WindowStyle DEFAULT_WINDOW_STYLE = WindowStyle::Windowed;

static constexpr Vec2<size_t> DEFAULT_WINDOW_SIZE = {
    DEFAULT_WINDOW_WIDTH,
    DEFAULT_WINDOW_HEIGHT
};

class Window {
public:
    class Impl;
    explicit Window(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    ~Window();
    Window(const Window&)           = delete;
    Window operator=(const Window&) = delete;
    Window(Window&&)                = default;
    Window& operator=(Window&&)     = default;
    void    draw(const drawing::Image& image);
    void    set_style(WindowStyle style);
    void    render_frame();
    bool    next_frame();
    [[nodiscard]]
    bool should_close() const;
    [[nodiscard]]
    const size_t& buf_width() const;
    [[nodiscard]]
    const size_t& buf_height() const;

private:
    friend class Impl;
    Impl* m_impl;
};
} // namespace core::window
