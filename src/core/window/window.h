#pragma once
#include "core/math/vector.h"
#include <string>

namespace core {
namespace window {

//! Window display styles
enum class WindowStyle {
    Windowed,           //!< Windowed mode (resizable)
    WindowedFullscreen, //!< Windowed mode with no decorations (resizable)
    Fullscreen,         //!< Fullscreen mode
};

static constexpr size_t                    DEFAULT_WINDOW_WIDTH  = 640;
static constexpr size_t                    DEFAULT_WINDOW_HEIGHT = 480;
static constexpr std::string               DEFAULT_WINDOW_TITLE  = "RayGame";
static constexpr core::window::WindowStyle DEFAULT_WINDOW_STYLE =
    core::window::WindowStyle::Windowed;
static constexpr Vec2<size_t> DEFAULT_WINDOW_SIZE = {
    DEFAULT_WINDOW_WIDTH,
    DEFAULT_WINDOW_HEIGHT
};

} // namespace window

template<typename Derived>
class Window {
protected:
    bool                      m_should_close = false;
    core::Vec2<size_t>        m_size;
    std::string               m_title;
    core::window::WindowStyle m_style;

    Window(
        core::Vec2<size_t>        size  = core::window::DEFAULT_WINDOW_SIZE,
        std::string               title = core::window::DEFAULT_WINDOW_TITLE,
        core::window::WindowStyle style = core::window::DEFAULT_WINDOW_STYLE
    )
        : m_size(std::move(size))
        , m_title(std::move(title))
        , m_style(std::move(style)) {}

    ~Window() = default;

public:
    Window(Window&)           = delete;
    Window operator=(Window&) = delete;

    Window(Window&&)            = default;
    Window& operator=(Window&&) = default;

    inline void set_style(this Derived& self, core::window::WindowStyle style) {
        self.set_style(style);
    }

    inline bool next_frame(this Derived& self) {
        self.next_frame();
    }

    inline bool should_close() {
        return m_should_close;
    }
};

} // namespace core
