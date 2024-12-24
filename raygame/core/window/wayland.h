#pragma once
#include "raygame/core/window/window.h"

namespace core::window {
namespace detail {
class WaylandImpl;
}

class WaylandWindow: public Window<WaylandWindow> {
public:
    WaylandWindow(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    ~WaylandWindow();
    void set_style(WindowStyle style);
    bool next_frame();

    bool should_close();

private:
    friend class detail::WaylandImpl;
    detail::WaylandImpl* m_wayland_impl;

    void new_buffer(const Vec2<size_t>& size);
    void new_buffer();
};

} // namespace core::window
