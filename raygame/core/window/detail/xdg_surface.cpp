#include "raygame/core/window/detail/wayland.h"

void core::window::detail::WaylandImpl::xdg_surface_handle_configure(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] xdg_surface* xdg_surface,
    [[maybe_unused]] uint32_t     serial
) {
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    xdg_surface_ack_configure(xdg_surface, serial);
    if (this_impl->m_configured) {
        wl_surface_commit(this_impl->m_wl_surface);
    }
    this_impl->m_configured = true;
}
