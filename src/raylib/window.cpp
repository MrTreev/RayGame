#include "raylib/window.h"
#include "utils/logger.h"
#include <raylib.h>

namespace raylib {

Window::Window(int width, int height, const std::string title) {
    utils::log::trace("Initialising Window");
    InitWindow(width, height, title.c_str());
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

bool Window::is_ready() {
    const bool win_is_ready = IsWindowReady();
    utils::log::trace("Window is ready: ");
    return win_is_ready;
};

bool Window::is_fullscreen(){};

bool Window::is_hidden(){};

bool Window::is_maximised(){};

bool Window::is_minimised(){};

bool Window::is_focused(){};

bool Window::is_resized(){};

void Window::set_state(flag_t flags){};

void Window::check_state(flag_t flag){};

void Window::clear_state(flag_t flags){};

void Window::toggle_fullscreen(){};

void Window::toggle_borderless(){};

void Window::maximise(){};

void Window::minimise(){};

void Window::restore(){};

void Window::set_icon(raylib::Image image){};

} // namespace raylib
