#include "raygame/core/application/detail/wayland.h"
#include "raygame/core/types.h"
#include <wayland-client-protocol.h>

const wl_callback_listener core::detail::AppImplWayland::m_wl_surface_frame_listener{
    .done = wl_surface_handle_done,
};

void core::detail::AppImplWayland::wl_surface_handle_done(
    void*                     data,
    wl_callback*              wl_callback,
    [[maybe_unused]] uint32_t time
) {
    auto* this_impl = static_cast<AppImplWayland*>(data);
    wl_callback_destroy(wl_callback);
    wl_callback = wl_surface_frame(this_impl->m_wl_surface);
    wl_callback_add_listener(wl_callback, &m_wl_surface_frame_listener, this_impl);
    this_impl->new_buffer();
    wl_surface_attach(this_impl->m_wl_surface, this_impl->m_wl_buffer, 0, 0);
    wl_buffer_destroy(this_impl->m_wl_buffer);
    this_impl->m_wl_buffer = nullptr;
    const auto size        = this_impl->get_size();
    wl_surface_damage_buffer(
        this_impl->m_wl_surface,
        0,
        0,
        math::numeric_cast<int32_t>(size.m_x),
        math::numeric_cast<int32_t>(size.m_y)
    );
    wl_surface_commit(this_impl->m_wl_surface);
}
