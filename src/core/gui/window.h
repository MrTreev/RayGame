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
    Window();
    Window(const size_t& width, const size_t& height);
    Window(const size_t& width, const size_t& height, const std::string& name);
    Window(
        const size_t&      width,
        const size_t&      height,
        const std::string& name,
        const WindowStyle& style
    );
    ~Window();

    Window(const Window&)            = delete;
    Window(Window&&)                 = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&)      = delete;

    //! Reports if the window has been requested to close
    bool should_close();

    //! Clears the drawing buffer and begins drawing mode
    void clear();

    //! Swaps the display buffers and ends drawing mode
    void display();

    //! Sets whether the current FPS should be drawn to the screen
    void draw_fps(bool enable);

    //! Reports if the window is in windowed mode
    bool is_windowed();

    //! Reports if the window is in windowed-fullscreen mode
    bool is_windowed_fullscreen();

    //! Reports if the window is in fullscreen mode
    bool is_fullscreen();

    //! Sets the window style, @see WindowStyle
    void set_style(WindowStyle style);

    //! Sets the target framerate
    /*!
     * @param   name Target framerate
     * @pre     The framerate is greater than zero and smaller than the maximum
     *          value supported by the implementation
     */
    void set_framerate(const size_t& framerate);

    //! Sets the window size
    void set_size(const size_t& width, const size_t& height);

    //! Set fullscreen mode
    void set_fullscreen(const bool& enable);

    //! Toggle fullscreen mode
    void toggle_fullscreen();

    //! Reports the current window style, @see WindowStyle
    WindowStyle get_style();

    //! Reports the current average framerate
    size_t get_framerate();

private:
    bool _draw_fps{false};
};

} // namespace core::gui
