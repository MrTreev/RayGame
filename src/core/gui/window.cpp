#include "core/gui/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "main.h"
#include <limits>
#include <string_view>

// Raylib
#include <raylib.h>

core::gui::Window::Window()
    : core::gui::Window(config::window_width, config::window_height) {}

core::gui::Window::Window(const size_t& width, const size_t& height)
    : core::gui::Window(width, height, config::game_name) {}

core::gui::Window::Window(
    const size_t&    width,
    const size_t&    height,
    std::string_view name
)
    : core::gui::Window(width, height, name, WindowStyle::Windowed) {}

core::gui::Window::Window(
    const size_t&      width,
    const size_t&      height,
    std::string_view   name,
    const WindowStyle& style
) {
    core::condition::pre_condition(
        width <= std::numeric_limits<int>::max(),
        "width is too large for Raylib int type"
    );
    core::condition::pre_condition(
        height <= std::numeric_limits<int>::max(),
        "height is too large for Raylib int type"
    );

    ::InitWindow(
        static_cast<int>(width),
        static_cast<int>(height),
        name.data()
    );
    switch (style) {
    case WindowStyle::Windowed: ::SetConfigFlags(FLAG_WINDOW_RESIZABLE); break;
    case WindowStyle::WindowedFullscreen:
        ::SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED);
        break;
    case WindowStyle::Fullscreen: ::SetConfigFlags(FLAG_FULLSCREEN_MODE); break;
    }
    core::condition::post_condition(
        ::IsWindowReady(),
        "Failed to create Window"
    );
}

core::gui::Window::~Window() {
    if (::IsWindowReady()) {
        ::CloseWindow();
    }
}
