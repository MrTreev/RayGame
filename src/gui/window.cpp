#include "gui/window.h"

namespace gui {

Window::Window(
    const std::string& title,
    const int32_t&     width,
    const int32_t&     height,
    const uint32_t&    flags
)
    : _title(title) {
    if (flags != 0) {
        ::SetConfigFlags(flags);
    }
    ::InitWindow(width, height, title.c_str());
    if (!::IsWindowReady()) {
        utils::log::fatal("Failed to create Window");
        throw std::runtime_error("Failed to create Window");
    }
}

Window::~Window() {
    ::CloseWindow();
}

void Window::resize(int height, int width) {
    ::SetWindowSize(width, height);
}

void Window::start_frame() {
    ::BeginDrawing();
    clear_background();
}

void Window::end_frame() {
    ::EndDrawing();
}

bool Window::should_close() {
    return ::WindowShouldClose();
}

bool Window::next() {
    return !should_close();
}

float Window::delta_time() {
    return ::GetFrameTime();
}

void Window::clear_background() {
    ::ClearBackground(gui::colour::black.col());
}

void Window::SetConfigFlags(config_t flags) {
    ::SetConfigFlags(flags.bits);
}

} // namespace gui
