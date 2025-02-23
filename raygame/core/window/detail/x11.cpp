#include "raygame/core/window/detail/x11.h"
#if defined(RAYGAME_GUI_BACKEND_X11)
#    include "raygame/core/condition.h"
#    include <utility>

namespace core::window::detail {
namespace {
using core::condition::unimplemented;
using core::condition::unreachable;
} // namespace

X11WindowImpl::X11WindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style) {
    if constexpr (config::EnabledBackends::x11()) {
        constexpr auto background_colour = 0xFF'DD'00;
        m_display                        = XOpenDisplay(nullptr);
        m_window                         = XCreateSimpleWindow(
            m_display, // our connection to server
            RootWindow(m_display, 0), // parent window (none in this example)
            0,                        // x
            0,                        // y
            math::numeric_cast<uint32_t>(size.x), // width
            math::numeric_cast<uint32_t>(size.y), // height
            0,          // border width
            0x00'00'00, // border color (ignored in this example)
            background_colour // background color (mustard yellow)
        );
        XStoreName(m_display, m_window, title.c_str());
        XMapWindow(m_display, m_window);
        XFlush(m_display);
        std::ignore = m_event;
        std::ignore = m_screen;
    } else {
        unreachable();
    }
}

X11WindowImpl::~X11WindowImpl() {
    if constexpr (config::EnabledBackends::x11()) {
        XUnmapWindow(m_display, m_window);
        XDestroyWindow(m_display, m_window);
        XCloseDisplay(m_display);
    } else {
        std::unreachable();
    }
}

void X11WindowImpl::draw(const drawing::ImageView& image) {
    if constexpr (config::EnabledBackends::x11()) {
        std::ignore = image;
        unimplemented();
    } else {
        unreachable();
    }
}

void X11WindowImpl::restyle(WindowStyle style) {
    if constexpr (config::EnabledBackends::x11()) {
        std::ignore = style;
        unimplemented();
    } else {
        unreachable();
    }
}

void X11WindowImpl::render_frame() {
    if constexpr (config::EnabledBackends::x11()) {
        unimplemented();
    } else {
        unreachable();
    }
}

bool X11WindowImpl::next_frame() {
    if constexpr (config::EnabledBackends::x11()) {
        unimplemented();
    } else {
        unreachable();
    }
}

bool X11WindowImpl::should_close() const {
    if constexpr (config::EnabledBackends::x11()) {
        unimplemented();
    } else {
        unreachable();
    }
}
} // namespace core::window::detail
#endif
