#include "raygame/core/window/detail/x11.h"
#if defined(RAYGAME_GUI_BACKEND_X11)
#    include "raygame/core/condition.h"
#    include <utility>

namespace core::window::detail {
using core::condition::unimplemented;
using core::condition::unreachable;

X11WindowImpl::X11WindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style) {
    if constexpr (config::EnabledBackends::x11()) {
        std::ignore = m_display;
        std::ignore = m_screen;
        std::ignore = m_event;
        std::ignore = m_window;
    } else {
        unreachable();
    }
}

X11WindowImpl::~X11WindowImpl() {
    if constexpr (config::EnabledBackends::x11()) {
        // XCloseDisplay(m_display);
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
