#include "raylib/window.h"
#include "utils/logger.h"
#include <raylib.h>

namespace raylib {

Window::Window(int width, int height, const std::string title) {
    InitWindow(width, height, title.c_str());
    utils::log::trace("Initialised Window");
}

Window::~Window() {
    CloseWindow();
    utils::log::trace("Destroyed Window");
}

bool Window::should_close() {
    const bool win_should_close = WindowShouldClose();
    utils::log::trace("Window should close: ");
    return win_should_close;
}

} // namespace raylib
