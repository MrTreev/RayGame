#include "raygame/core/window/wayland.h" //IWYU pragma: keep
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

void core::window::WaylandWindow::draw_line(
    std::span<const Pixel> line,
    Vec2<size_t>           pos
) {
    const std::span line_view{m_impl.data_row(pos.y), m_impl.buf_width()};
    for (size_t idx{0}; idx < line.size() - 1; ++idx) {
        const auto& pixel        = line[idx];
        line_view[(4 * idx) + 0] = pixel.m_red;
        line_view[(4 * idx) + 1] = pixel.m_green;
        line_view[(4 * idx) + 2] = pixel.m_blue;
        line_view[(4 * idx) + 3] = pixel.m_alpha;
    }
}

void core::window::WaylandWindow::draw(const drawing::Image& image) {
    for (size_t col{0}; col < image.height(); ++col) {
        draw_line(image.row(col), {0, col});
    }
}
