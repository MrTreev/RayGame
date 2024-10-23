#include "core/window/x11.h" // IWYU pragma: keep
#include "core/base/condition.h"
#include "core/math/numeric_cast.h"

core::window::X11Window::X11Window(
    core::Vec2<size_t>        size,
    std::string               title,
    core::window::WindowStyle style
)
    : Window(size, title, style) {
    using core::condition::check_ptr;
    using core::math::numeric_cast;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
    m_display = XOpenDisplay(nullptr);
    check_ptr(m_display, "Could not open Display");
    m_screen = DefaultScreen(m_display);
    m_window = XCreateSimpleWindow(
        m_display,
        RootWindow(m_display, m_screen),
        0,
        0,
        numeric_cast<uint32_t>(size.x),
        numeric_cast<uint32_t>(size.y),
        1U,
        WhitePixel(m_display, m_screen),
        BlackPixel(m_display, m_screen)
    );
    XSelectInput(m_display, m_window, ExposureMask | KeyPressMask);
    XMapWindow(m_display, m_window);
#pragma clang diagnostic pop
}

core::window::X11Window::~X11Window() {
    XCloseDisplay(m_display);
}

bool core::window::X11Window::next_frame() {
    using core::condition::check_ptr;
    using core::math::numeric_cast;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
    XNextEvent(m_display, &m_event);
    if (m_event.type == Expose) {
        // Draw stuff here
    }
    if (m_event.type == KeyPress) {
        return false;
    } else {
        return true;
    }
#pragma clang diagnostic pop
}
