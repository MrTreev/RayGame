#include "raygame/core/window/wayland.h" //IWYU pragma: keep
#include <utility>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>

core::window::WaylandWindow::WaylandWindow(
    core::Vec2<size_t> size,
    std::string        title,
    WindowStyle        style
)
    : Window(size, std::move(title), style)
    , m_impl(this) {}

core::window::WaylandWindow::~WaylandWindow() = default;

void core::window::WaylandWindow::set_style(WindowStyle style) {
    m_impl.set_style(style);
}

void core::window::WaylandWindow::render_frame() {
    m_impl.render_frame();
}
