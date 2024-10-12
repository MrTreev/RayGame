#pragma once
#include "core/types.h"
#include <string>

namespace core {

enum class WindowBackend {
    Wayland,
};

//! Window display styles
enum class WindowStyle {
    Windowed,           //!< Windowed mode (resizable)
    WindowedFullscreen, //!< Windowed mode with no decorations (resizable)
    Fullscreen,         //!< Fullscreen mode
};

static constexpr size_t            DEFAULT_WINDOW_WIDTH  = 640;
static constexpr size_t            DEFAULT_WINDOW_HEIGHT = 480;
static constexpr std::string       DEFAULT_WINDOW_TITLE  = "RayGame";
static constexpr core::WindowStyle DEFAULT_WINDOW_STYLE =
    core::WindowStyle::Windowed;
static constexpr Vec2<size_t> DEFAULT_WINDOW_SIZE = {
    DEFAULT_WINDOW_WIDTH,
    DEFAULT_WINDOW_HEIGHT
};

class Window {
protected:
    bool         m_should_close = false;
    Vec2<size_t> m_size;

    Window(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    ~Window();

public:
    Window(Window&)             = delete;
    Window(Window&&)            = delete;
    Window  operator=(Window&)  = delete;
    Window& operator=(Window&&) = delete;

    void set_style(WindowStyle style);
    void new_buffer(Vec2<size_t> size);
    bool should_close();

    inline void new_buffer() {
        new_buffer(m_size);
    }
};

} // namespace core
