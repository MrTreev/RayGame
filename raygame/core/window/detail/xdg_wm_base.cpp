#include "raygame/core/window/detail/wayland.h"

const xdg_wm_base_listener
    core::window::detail::WaylandImpl::m_xdg_wm_base_listener = {
        .ping = xdg_wm_base_handle_ping,
};

void core::window::detail::WaylandImpl::xdg_wm_base_handle_ping(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] xdg_wm_base* xdg_wm_base,
    [[maybe_unused]] uint32_t     serial
) {
    [[maybe_unused]]
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    xdg_wm_base_pong(xdg_wm_base, serial);
}
