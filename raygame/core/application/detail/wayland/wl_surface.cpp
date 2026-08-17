#include "raygame/core/application/detail/wayland.hpp"
#include "raygame/core/application/detail/wayland/wl_include.hpp"
#include "raygame/core/types.hpp"

const wl_callback_listener core::detail::AppImplWayland::m_wl_surface_frame_listener{
    .done = wl_surface_handle_done,
};

void core::detail::AppImplWayland::wl_surface_handle_done(
    void*                     data,
    wl_callback*              wl_callback,
    [[maybe_unused]] uint32_t time
) {
    auto* self = static_cast<AppImplWayland*>(data);

    wl_callback_destroy(wl_callback);
    self->m_wl_callback = wl_surface_frame(self->m_wl_surface);
    wl_callback_add_listener(self->m_wl_callback, &m_wl_surface_frame_listener, self);

    // Make sure we have buffers matching the current size
    self->recreate_buffers();

    // Attach the buffer we have been drawing into
    const size_t front = self->m_current_buffer;
    wl_surface_attach(self->m_wl_surface, self->m_buffers.at(front), 0, 0);
    self->m_busy.at(front) = true;

    const auto size = self->get_size();
    wl_surface_damage_buffer(
        self->m_wl_surface,
        0,
        0,
        math::numeric_cast<int32_t>(size.m_x),
        math::numeric_cast<int32_t>(size.m_y)
    );
    wl_surface_commit(self->m_wl_surface);

    // Switch to the other buffer for the next frame (if it is free)
    const size_t next = 1 - front;
    if (!self->m_busy.at(next)) {
        self->m_current_buffer = next;
        self->set_current_pixbuf();
    }
    // else: both busy – keep drawing into the same buffer (or you could
    //       dispatch until a release arrives; rare for software rendering)}
}
