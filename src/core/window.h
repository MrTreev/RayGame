#pragma once
#include "core/types.h"
#include <string>

namespace core {

//! Window display styles
enum class WindowStyle {
    Windowed,           //!< Windowed mode (resizable)
    WindowedFullscreen, //!< Windowed mode with no decorations (resizable)
    Fullscreen,         //!< Fullscreen mode
};

class Window {
    std::string m_title{DEFAULT_WINDOW_NAME};
    size_t      m_width{0};
    size_t      m_height{0};
    size_t      m_buffer_size{0};

    static constexpr decltype(m_height) DEFAULT_WINDOW_WIDTH  = 640;
    static constexpr decltype(m_height) DEFAULT_WINDOW_HEIGHT = 480;
    static constexpr decltype(m_title)  DEFAULT_WINDOW_NAME   = "RayGame";
    static constexpr core::WindowStyle  DEFAULT_WINDOW_STYLE =
        core::WindowStyle::Windowed;

public:
    //! Window initialiser
    /*!
     * @param   width   Width of the window
     * @param   height  Height of the window
     * @param   title   Title of the window
     * @param   style   Style of the window
     *
     * @post    The Window is created correctly
     */
    explicit Window(
        const decltype(m_height)& width  = DEFAULT_WINDOW_WIDTH,
        const decltype(m_height)& height = DEFAULT_WINDOW_HEIGHT,
        decltype(m_title)         title  = DEFAULT_WINDOW_NAME,
        const WindowStyle&        style  = DEFAULT_WINDOW_STYLE
    );
    explicit Window(
        const core::Vec2<decltype(m_height)>& size,
        decltype(m_title)                     title = DEFAULT_WINDOW_NAME,
        const WindowStyle&                    style = DEFAULT_WINDOW_STYLE
    );
    ~Window();

    Window(const Window&)            = delete;
    Window(Window&&)                 = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&)      = delete;

    //! Reports if the window has been requested to close
    [[nodiscard]]
    static bool should_close();

    //! Renders a frame
    void render() const;
};

} // namespace core
