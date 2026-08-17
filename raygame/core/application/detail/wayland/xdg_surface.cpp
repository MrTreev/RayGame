#include "raygame/core/application/detail/wayland.hpp"
#include "raygame/core/application/detail/wayland/wl_include.hpp"
#include "raygame/core/types.hpp"

const xdg_surface_listener core::detail::AppImplWayland::m_xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};

void core::detail::AppImplWayland::xdg_surface_handle_configure(
    void*        data,
    xdg_surface* xdg_surface,
    uint32_t     serial
) {
    auto* this_impl = static_cast<AppImplWayland*>(data);
    if (this_impl->m_should_close) {
        return;
    }
    xdg_surface_ack_configure(xdg_surface, serial);
    if (this_impl->m_configured) {
        wl_surface_commit(this_impl->m_wl_surface);
    }
    this_impl->m_configured = true;
}
