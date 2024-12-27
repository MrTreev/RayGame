#include "raygame/core/window/detail/wayland.h"

void core::window::detail::WaylandImpl::wl_surface_draw_frame(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_callback* wl_callback,
    [[maybe_unused]] uint32_t     time
) {
    using core::math::numeric_cast;
    wl_callback_destroy(wl_callback);
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    wl_callback            = wl_surface_frame(this_impl->m_wl_surface);
    wl_callback_add_listener(
        wl_callback,
        &m_wl_surface_frame_listener,
        this_impl
    );
    this_impl->new_buffer(this_impl->m_size);
    wl_surface_attach(this_impl->m_wl_surface, this_impl->m_wl_buffer, 0, 0);
    wl_surface_damage_buffer(
        this_impl->m_wl_surface,
        0,
        0,
        numeric_cast<int32_t>(this_impl->m_size.x),
        numeric_cast<int32_t>(this_impl->m_size.y)
    );
    wl_surface_commit(this_impl->m_wl_surface);
    this_impl->m_last_frame = time;
}

const wl_callback_listener
    core::window::detail::WaylandImpl::m_wl_surface_frame_listener{
        .done = wl_surface_draw_frame,
    };
