#include "raygame/core/window/wayland.h"
#include <xdg-shell-client-protocol.h>

const xdg_wm_base_listener&
    // NOLINTNEXTLINE(*-reference-to-constructed-temporary)
    core::window::detail::WaylandImpl::m_xdg_wm_base_listener = {
        .ping = xdg_wm_base_handle_ping,
};

void core::window::detail::WaylandImpl::xdg_wm_base_handle_ping(
    void*        data,
    xdg_wm_base* xdg_wm_base,
    uint32_t     serial
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<WaylandImpl*>(data);
    xdg_wm_base_pong(xdg_wm_base, serial);
}