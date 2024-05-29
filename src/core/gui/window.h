#pragma once
#include "core/types.h"
#include <string_view>

namespace core::gui {

enum class WindowStyle {
    Windowed,
    WindowedFullscreen,
    Fullscreen,
};

class Window {
public:
    //! Window initialiser
    /*!
	 * @param	width	Width of the window
	 * @param	height	Height of the window
	 * @param	name	Name of the window
	 * @param	style	Style of the window
	 *
	 * @pre		The width is greater than zero and smaller than the maximum
	 * 			value supported by the implementation @see RAYGAME_BACKEND
	 * @pre		The height is greater than zero and smaller than the maximum
	 * 			value supported by the implementation @see RAYGAME_BACKEND
	 * @post 	The Window is created correctly
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

    bool should_close();

    void clear();
    void display();
    void draw_fps(bool enable);

    bool is_windowed();
    bool is_windowed_fullscreen();
    bool is_fullscreen();

    void set_style(WindowStyle style);
    void set_framerate(const size_t& framerate);
    void set_size(const size_t& width, const size_t& height);
    void set_fullscreen(const bool& enable);

    void toggle_fullscreen();

    WindowStyle get_style();
    size_t      get_framerate();

private:
    bool _draw_fps{false};
};

} // namespace core::gui
