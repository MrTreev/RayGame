#include "raylib/window.h"

namespace raylib {

Window::Window(int width, int height, const std::string title) {
    InitWindow(width, height, title.c_str());
}

Window::~Window() {
    CloseWindow();
}

} // namespace raylib
