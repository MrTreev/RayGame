#pragma once
#include "core/types.h"
#include <string>

namespace core {

//! Window display styles
enum class WindowStyle {
    Windowed,           //< Windowed mode (resizable)
    WindowedFullscreen, //< Windowed mode with no decorations (resizable)
    Fullscreen,         //< Fullscreen mode
};

namespace {
constexpr size_t             DEFAULT_WINDOW_WIDTH  = 640;
constexpr size_t             DEFAULT_WINDOW_HEIGHT = 480;
constexpr core::Vec2<size_t> DEFAULT_WINDOW_SIZE   = {
    DEFAULT_WINDOW_WIDTH,
    DEFAULT_WINDOW_HEIGHT
};
constexpr std::string       DEFAULT_WINDOW_NAME  = "RayGame";
constexpr core::WindowStyle DEFAULT_WINDOW_STYLE = core::WindowStyle::Windowed;
} // namespace

class Window {
    std::string m_title{};
    size_t      m_width{0};
    size_t      m_height{0};
    size_t      m_buffer_size{0};

public:
    //! Window initialiser
    /*!
     * @param   width    Width of the window
     * @param   height    Height of the window
     * @param   name    Name of the window
     * @param   style    Style of the window
     *
     * @post    The Window is created correctly
     */
    explicit Window(
        const size_t&      width  = DEFAULT_WINDOW_WIDTH,
        const size_t&      height = DEFAULT_WINDOW_HEIGHT,
        std::string        title  = DEFAULT_WINDOW_NAME,
        const WindowStyle& style  = DEFAULT_WINDOW_STYLE
    );
    explicit Window(
        const core::Vec2<decltype(m_height)>& size,
        std::string                           title = DEFAULT_WINDOW_NAME,
        const WindowStyle&                    style = DEFAULT_WINDOW_STYLE
    );
    ~Window();

    Window(const Window&)            = delete;
    Window(Window&&)                 = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&)      = delete;

    //! Reports if the window has been requested to close
    bool should_close();
    void render();
};

} // namespace core
