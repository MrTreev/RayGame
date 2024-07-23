#pragma once
#include "core/window.h"
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

namespace core::window::wayland {
struct wl_buffer* create_buffer(
    const size_t& width,
    const size_t& height,
    const size_t& buffer_size
);

void init_window(
    const size_t&            width,
    const size_t&            height,
    const size_t&            buffer_size,
    const std::string&       title,
    const core::WindowStyle& style
);

void destroy_window();

void render_frame(const size_t& width, const size_t& height);

bool should_close();

} // namespace core::window::wayland
