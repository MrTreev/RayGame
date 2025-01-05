#include "raygame/core/window/detail/wayland.h"

core::window::detail::WaylandWindowImpl::WaylandWindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style) {}

core::window::detail::WaylandWindowImpl::~WaylandWindowImpl() = default;

void core::window::detail::WaylandWindowImpl::draw(const drawing::Image& image
) {
    std::ignore = image;
}

void core::window::detail::WaylandWindowImpl::restyle(WindowStyle style) {
    std::ignore = style;
}

void core::window::detail::WaylandWindowImpl::render_frame() {}

bool core::window::detail::WaylandWindowImpl::next_frame() {
    return false;
}

bool core::window::detail::WaylandWindowImpl::should_close() const {
    return true;
}
