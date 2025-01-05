#include "raygame/core/window/detail/x11.h"
#include "raygame/core/condition.h"
#include <utility>

core::window::detail::X11WindowImpl::X11WindowImpl(
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
        core::condition::unreachable();
    }
}

core::window::detail::X11WindowImpl::~X11WindowImpl() {
    if constexpr (config::EnabledBackends::x11()) {
        //XCloseDisplay(m_display);
    } else {
        std::unreachable();
    }
}

void core::window::detail::X11WindowImpl::draw(const drawing::Image& image) {
    if constexpr (config::EnabledBackends::x11()) {
        std::ignore = image;
        condition::unimplemented();
    } else {
        core::condition::unreachable();
    }
}

void core::window::detail::X11WindowImpl::restyle(WindowStyle style) {
    if constexpr (config::EnabledBackends::x11()) {
        std::ignore = style;
        condition::unimplemented();
    } else {
        core::condition::unreachable();
    }
}

void core::window::detail::X11WindowImpl::render_frame() {
    if constexpr (config::EnabledBackends::x11()) {
        condition::unimplemented();
    } else {
        core::condition::unreachable();
    }
}

bool core::window::detail::X11WindowImpl::next_frame() {
    if constexpr (config::EnabledBackends::x11()) {
        condition::unimplemented();
    } else {
        core::condition::unreachable();
    }
}

bool core::window::detail::X11WindowImpl::should_close() const {
    if constexpr (config::EnabledBackends::x11()) {
        condition::unimplemented();
    } else {
        core::condition::unreachable();
    }
}
