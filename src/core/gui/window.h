#pragma once
#include "core/types.h"
#include <string>

namespace core::gui {

//! Window display styles
enum class WindowStyle {
    Windowed,           //< Windowed mode (resizable)
    WindowedFullscreen, //< Windowed mode with no decorations (resizable)
    Fullscreen,         //< Fullscreen mode
};

class Window {
public:
    //! Window initialiser
    /*!
     * @param   width    Width of the window
     * @param   height    Height of the window
     * @param   name    Name of the window
     * @param   style    Style of the window
     *
     * @pre     The width is greater than zero and smaller than the maximum
     *          value supported by the implementation
     * @pre     The height is greater than zero and smaller than the maximum
     *          value supported by the implementation
     * @post    The Window is created correctly
     */
    explicit Window(
        const size_t&      width  = 640,
        const size_t&      height = 480,
        const std::string& name   = "RayGame",
        const WindowStyle& style  = WindowStyle::Windowed
    );
    ~Window();

    Window(const Window&)            = delete;
    Window(Window&&)                 = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&)      = delete;

    //! Reports if the window has been requested to close
    bool should_close();
};

} // namespace core::gui
