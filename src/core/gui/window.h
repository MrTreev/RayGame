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
    Window();
    Window(const size_t& width, const size_t& height);
    Window(const size_t& width, const size_t& height, std::string_view name);
    Window(
        const size_t&      width,
        const size_t&      height,
        std::string_view   name,
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
