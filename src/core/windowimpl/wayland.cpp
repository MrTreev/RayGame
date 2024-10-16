#include "core/windowimpl/wayland.h" //IWYU pragma: keep
#include "core/windowimpl/wayland_impl.h"
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>

core::window::WaylandWindow::WaylandWindow(
    core::Vec2<size_t>        size,
    std::string               title,
    core::window::WindowStyle style
)
    : Window(size, title, style)
    , m_wayland_impl(new detail::WaylandImpl(size, title, style)) {}

core::window::WaylandWindow::~WaylandWindow() {
    delete m_wayland_impl;
}

void core::window::WaylandWindow::new_buffer() {
    new_buffer(m_size);
}

void core::window::WaylandWindow::new_buffer(const Vec2<size_t>& size) {
    m_wayland_impl->new_buffer(size);
}

void core::window::WaylandWindow::set_style(core::window::WindowStyle style) {
    m_wayland_impl->set_style(style);
}

bool core::window::WaylandWindow::next_frame() {
    if (!should_close()) {
        m_wayland_impl->next_frame();
    }
    return !should_close();
}

bool core::window::WaylandWindow::should_close() {
    return m_wayland_impl->should_close();
}
