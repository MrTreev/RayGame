#include "raygame/core/window/detail/wayland.h"
#include <xdg-shell-client-protocol.h>

const xdg_wm_base_listener core::window::detail::WaylandWindowImpl::m_xdg_wm_base_listener = {
    .ping = xdg_wm_base_handle_ping,
};

void core::window::detail::WaylandWindowImpl::xdg_wm_base_handle_ping(
    void*        data,
    xdg_wm_base* xdg_wm_base,
    uint32_t     serial
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<WaylandWindowImpl*>(data);
    xdg_wm_base_pong(xdg_wm_base, serial);
}
