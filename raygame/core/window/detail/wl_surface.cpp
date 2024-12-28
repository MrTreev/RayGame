#include "raygame/core/window/wayland.h"
#include <wayland-client-protocol.h>

const wl_callback_listener&
    // NOLINTNEXTLINE(*-reference-to-constructed-temporary)
    core::window::detail::WaylandImpl::m_wl_surface_frame_listener{
        .done = wl_surface_handle_done,
    };

void core::window::detail::WaylandImpl::wl_surface_handle_done(
    void*        data,
    wl_callback* wl_callback,
    uint32_t     time
) {
    auto* this_impl = static_cast<WaylandImpl*>(data);
    wl_callback_destroy(wl_callback);
    wl_callback = wl_surface_frame(this_impl->m_wl_surface);
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
        math::numeric_cast<int32_t>(this_impl->m_size.x),
        math::numeric_cast<int32_t>(this_impl->m_size.y)
    );
    wl_surface_commit(this_impl->m_wl_surface);
    this_impl->m_last_frame = time;
}
