#include "raygame/core/window/detail/wayland.h"

const xdg_toplevel_listener
    core::window::detail::WaylandImpl::m_xdg_toplevel_listener = {
        .configure        = xdg_toplevel_handle_configure,
        .close            = xdg_toplevel_handle_close,
        .configure_bounds = xdg_toplevel_handle_configure_bounds,
        .wm_capabilities  = xdg_toplevel_handle_wm_capabilities,
};

void core::window::detail::WaylandImpl::xdg_toplevel_handle_configure(
    [[maybe_unused]] void*                data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t              width,
    [[maybe_unused]] int32_t              height,
    [[maybe_unused]] struct wl_array*     states
) {
    [[maybe_unused]]
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
}

void core::window::detail::WaylandImpl::xdg_toplevel_handle_close(
    [[maybe_unused]] void*                data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel
) {
    [[maybe_unused]]
    WaylandImpl* this_impl    = static_cast<WaylandImpl*>(data);
    this_impl->m_should_close = true;
}

void core::window::detail::WaylandImpl::xdg_toplevel_handle_configure_bounds(
    [[maybe_unused]] void*                data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t              width,
    [[maybe_unused]] int32_t              height
) {
    [[maybe_unused]]
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
}

void core::window::detail::WaylandImpl::xdg_toplevel_handle_wm_capabilities(
    [[maybe_unused]] void*                data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] struct wl_array*     capabilities
) {
    [[maybe_unused]]
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
}
