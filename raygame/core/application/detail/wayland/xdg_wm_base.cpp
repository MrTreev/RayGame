#include "raygame/core/application/detail/wayland.h"
#include "raygame/core/types.h"
#include <xdg-shell-client-protocol.h>

const xdg_wm_base_listener core::detail::AppImplWayland::m_xdg_wm_base_listener = {
    .ping = xdg_wm_base_handle_ping,
};

void core::detail::AppImplWayland::xdg_wm_base_handle_ping(
    void*        data,
    xdg_wm_base* xdg_wm_base,
    uint32_t     serial
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<AppImplWayland*>(data);
    xdg_wm_base_pong(xdg_wm_base, serial);
}
