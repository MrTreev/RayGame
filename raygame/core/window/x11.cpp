#include "raygame/core/window/x11.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include "raygame/core/math/numeric_cast.h"
#include <utility>

core::window::X11Window::X11Window(
    core::Vec2<size_t> size,
    std::string        title,
    WindowStyle        style
)
    : Window(size, std::move(title), style)
    , m_display(XOpenDisplay(nullptr))
    , m_screen(DefaultScreen(m_display))
    , m_window(XCreateSimpleWindow(
          m_display,
          RootWindow(m_display, m_screen),
          0,
          0,
          math::numeric_cast<uint32_t>(size.x),
          math::numeric_cast<uint32_t>(size.y),
          1U,
          WhitePixel(m_display, m_screen),
          BlackPixel(m_display, m_screen)
      )) {
    core::condition::check_ptr(m_display, "Could not open Display");
    XSelectInput(m_display, m_window, ExposureMask | KeyPressMask);
    XMapWindow(m_display, m_window);
}

core::window::X11Window::~X11Window() {
    XCloseDisplay(m_display);
}

void core::window::X11Window::render_frame() {
    XNextEvent(m_display, &m_event);
    if (m_event.type == Expose) {
        // Draw stuff here
    }
    if (m_event.type == KeyPress) {
        set_close();
    }
}
