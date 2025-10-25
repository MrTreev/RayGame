#include "raygame/core/application/detail/wayland.h"
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

const xdg_surface_listener core::detail::AppImplWayland::m_xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};

void core::detail::AppImplWayland::xdg_surface_handle_configure(
    void*        data,
    xdg_surface* xdg_surface,
    uint32_t     serial
) {
    auto* this_impl = static_cast<AppImplWayland*>(data);
    xdg_surface_ack_configure(xdg_surface, serial);
    if (this_impl->m_configured) {
        wl_surface_commit(this_impl->m_wl_surface);
    }
    this_impl->m_configured = true;
}
