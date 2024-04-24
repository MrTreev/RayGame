#include "raylib/window.h"
#include "utils/logger.h"
#include <raylib.h>
#include <string>

namespace raylib {

Window::Window(int width, int height, const char *title) {
    utils::log::trace("Initialising Window");
    InitWindow(width, height, title);
}

Window::~Window() {
    CloseWindow();
    utils::log::trace("Destroyed Window");
}

bool Window::should_close() {
    const bool check = WindowShouldClose();
    utils::log::trace("Window should close: " +
                      std::string(check ? "true" : "false"));
    return check;
}

bool Window::is_ready() {
    const bool check = IsWindowReady();
    utils::log::trace("Window is ready: " +
                      std::string(check ? "true" : "false"));
    return check;
};

bool Window::is_fullscreen() {
    const bool check = IsWindowFullscreen();
    utils::log::trace("Window is fullscreen: " +
                      std::string(check ? "true" : "false"));
    return check;
};

bool Window::is_hidden() {
    const bool check = IsWindowHidden();
    utils::log::trace("Window is hidden: " +
                      std::string(check ? "true" : "false"));
    return check;
};

bool Window::is_maximised() {
    const bool check = IsWindowMaximized();
    utils::log::trace("Window is maximised: " +
                      std::string(check ? "true" : "false"));
    return check;
};

bool Window::is_minimised() {
    const bool check = IsWindowMinimized();
    utils::log::trace("Window is minimised: " +
                      std::string(check ? "true" : "false"));
    return check;
};

bool Window::is_focused() {
    const bool check = IsWindowFocused();
    utils::log::trace("Window is focused: " +
                      std::string(check ? "true" : "false"));
    return check;
};

bool Window::is_resized() {
    const bool check = IsWindowResized();
    utils::log::trace("Window is resized: " +
                      std::string(check ? "true" : "false"));
    return check;
};

void Window::set_state(flag_t flags) {
    utils::log::trace("Setting window state: " + std::to_string(flags));
    SetWindowState(flags);
};

bool Window::check_state(flag_t flag) {
    const bool check = IsWindowState(flag);
    utils::log::trace("Checking window state (" + std::to_string(flag) +
                      "): " + std::string(check ? "true" : "false"));
    return check;
};

void Window::clear_state(flag_t flags) {
    utils::log::trace("Clearing window state: " + std::to_string(flags));
    ClearWindowState(flags);
};

void Window::toggle_fullscreen() {
    utils::log::trace("Toggle Fullscreen");
    ToggleFullscreen();
};

void Window::toggle_borderless() {
    utils::log::trace("Toggle Borderless");
    ToggleBorderlessWindowed();
};

void Window::maximise() {
    utils::log::trace("Maximise Window");
    MaximizeWindow();
};

void Window::minimise() {
    utils::log::trace("Minimise Window");
    MinimizeWindow();
};

void Window::restore() {
    utils::log::trace("Restore Window");
    RestoreWindow();
};

void Window::set_icon(raylib::Image image) {
    utils::log::trace("Setting Window Icon");
    SetWindowIcon(image);
};

void Window::start_frame() {
    utils::log::trace("Frame Start");
    BeginDrawing();
    ClearBackground({0, 0, 0, 0});
};

void Window::end_frame() {
    utils::log::trace("Frame End");
    EndDrawing();
};

int Window::height() {
    const int height = GetScreenHeight();
    utils::log::trace("Screen height: " + std::to_string(height));
    return height;
};
int Window::width() {
    const int width = GetScreenWidth();
    utils::log::trace("Screen width: " + std::to_string(width));
    return width;
};

} // namespace raylib
