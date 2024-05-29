#include "core/gui/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "main.h"
#include <limits>
#include <string_view>

// Raylib
#include <raylib.h>

constexpr int rl_win_flags = static_cast<int>(
    static_cast<unsigned int>(FLAG_WINDOW_RESIZABLE)
    | static_cast<unsigned int>(FLAG_WINDOW_ALWAYS_RUN)
    | static_cast<unsigned int>(FLAG_VSYNC_HINT)
);
constexpr int rl_wfs_flags = static_cast<int>(
    static_cast<unsigned int>(FLAG_WINDOW_UNDECORATED)
    | static_cast<unsigned int>(FLAG_WINDOW_ALWAYS_RUN)
    | static_cast<unsigned int>(FLAG_WINDOW_MAXIMIZED)
    | static_cast<unsigned int>(FLAG_BORDERLESS_WINDOWED_MODE)
    | static_cast<unsigned int>(FLAG_VSYNC_HINT)
);
constexpr int rl_fsn_flags = static_cast<int>(
    static_cast<unsigned int>(FLAG_FULLSCREEN_MODE)
    | static_cast<unsigned int>(FLAG_WINDOW_UNDECORATED)
    | static_cast<unsigned int>(FLAG_VSYNC_HINT)
);

core::gui::Window::Window()
    : core::gui::Window(config::window_width, config::window_height) {}

core::gui::Window::Window(const size_t& width, const size_t& height)
    : core::gui::Window(width, height, config::game_name.data()) {}

core::gui::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name
)
    : core::gui::Window(width, height, name, WindowStyle::Windowed) {}

core::gui::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name,
    const WindowStyle& style
) {
    core::condition::pre_condition(
        ((width > 0) && (height > 0)),
        "Width and height must be greater than zero"
    );
    core::condition::pre_condition(
        (width <= std::numeric_limits<int>::max()),
        "Width is too large for Raylib int type"
    );
    core::condition::pre_condition(
        (height <= std::numeric_limits<int>::max()),
        "Height is too large for Raylib int type"
    );

    ::InitWindow(
        static_cast<int>(width),
        static_cast<int>(height),
        name.c_str()
    );
    core::condition::post_condition(
        ::IsWindowReady(),
        "Failed to create Window"
    );
    set_style(style);
    set_framerate(60);
}

core::gui::Window::~Window() {
    ::EndDrawing();
    if (::IsWindowReady()) {
        ::CloseWindow();
    }
}

bool core::gui::Window::should_close() {
    return ::WindowShouldClose();
}

void core::gui::Window::clear() {
    ::BeginDrawing();
    ::ClearBackground(BLACK);
    ::EndDrawing();
}

void core::gui::Window::display() {
    if (_draw_fps) {
        ::DrawFPS(10, 10);
    }
    ::EndDrawing();
    ::ClearBackground(BLACK);
    ::BeginDrawing();
}

void core::gui::Window::draw_fps(bool enable) {
    _draw_fps = enable;
}

bool core::gui::Window::is_windowed() {
    return ::IsWindowState(rl_win_flags);
}

bool core::gui::Window::is_windowed_fullscreen() {
    return ::IsWindowState(rl_wfs_flags);
}

bool core::gui::Window::is_fullscreen() {
    return ::IsWindowFullscreen();
}

void core::gui::Window::set_style(core::gui::WindowStyle style) {
    switch (style) {
    case WindowStyle::Windowed:
        ::SetConfigFlags(rl_win_flags);
        set_fullscreen(false);
        break;
    case WindowStyle::WindowedFullscreen:
        ::SetConfigFlags(rl_wfs_flags);
        set_fullscreen(false);
        break;
    case WindowStyle::Fullscreen:
        ::SetConfigFlags(rl_fsn_flags);
        set_fullscreen(true);
        break;
    }
}

void core::gui::Window::set_framerate(const size_t& framerate) {
    core::condition::pre_condition(
        (framerate <= std::numeric_limits<int>::max()),
        "framerate is too large for Raylib int type"
    );
    ::SetTargetFPS(static_cast<int>(framerate));
}

void core::gui::Window::set_size(const size_t& width, const size_t& height) {
    core::condition::pre_condition(
        ((width > 0) && (height > 0)),
        "Cannot have a width or height of 0"
    );
    core::condition::pre_condition(
        (width <= std::numeric_limits<int>::max()),
        "width is too large for Raylib int type"
    );
    core::condition::pre_condition(
        (height <= std::numeric_limits<int>::max()),
        "height is too large for Raylib int type"
    );
    ::SetWindowSize(static_cast<int>(width), static_cast<int>(height));
}

void core::gui::Window::set_fullscreen(const bool& enable) {
    if (enable) {
        if (!is_fullscreen()) {
            toggle_fullscreen();
        }
    } else {
        if (is_fullscreen()) {
            toggle_fullscreen();
        }
    };
}

void core::gui::Window::toggle_fullscreen() {
    ::ToggleFullscreen();
}

core::gui::WindowStyle core::gui::Window::get_style() {
    if (is_windowed()) {
        return WindowStyle::Windowed;
    }
    if (is_windowed_fullscreen()) {
        return WindowStyle::WindowedFullscreen;
    }
    if (is_fullscreen()) {
        return WindowStyle::Fullscreen;
    }
    core::condition::check_condition(false, "Invalid style");
    return WindowStyle::Windowed; // for static analysis
};
