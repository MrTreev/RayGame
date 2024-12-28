#include "raygame/core/window/wayland.h"
#include <xdg-shell-client-protocol.h>

const xdg_toplevel_listener&
    // NOLINTNEXTLINE(*-reference-to-constructed-temporary)
    core::window::detail::WaylandImpl::m_xdg_toplevel_listener = {
        .configure        = xdg_toplevel_handle_configure,
        .close            = xdg_toplevel_handle_close,
        .configure_bounds = xdg_toplevel_handle_configure_bounds,
        .wm_capabilities  = xdg_toplevel_handle_wm_capabilities,
};

//NOLINTBEGIN(*-easily-swappable-parameters)

void core::window::detail::WaylandImpl::xdg_toplevel_handle_configure(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t              width,
    [[maybe_unused]] int32_t              height,
    [[maybe_unused]] struct wl_array*     states
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<WaylandImpl*>(data);
}

void core::window::detail::WaylandImpl::xdg_toplevel_handle_close(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel
) {
    auto* this_impl = static_cast<WaylandImpl*>(data);
    this_impl->m_base->set_close();
}

void core::window::detail::WaylandImpl::xdg_toplevel_handle_configure_bounds(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t              width,
    [[maybe_unused]] int32_t              height
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<WaylandImpl*>(data);
}

void core::window::detail::WaylandImpl::xdg_toplevel_handle_wm_capabilities(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] struct wl_array*     capabilities
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<WaylandImpl*>(data);
}

//NOLINTEND(*-easily-swappable-parameters)
