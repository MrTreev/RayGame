#include "raygame/core/window/detail/wayland.h"
#include <xdg-shell-client-protocol.h>

const xdg_toplevel_listener
    core::window::detail::WaylandWindowImpl::m_xdg_toplevel_listener = {
        .configure        = xdg_toplevel_handle_configure,
        .close            = xdg_toplevel_handle_close,
        .configure_bounds = xdg_toplevel_handle_configure_bounds,
        .wm_capabilities  = xdg_toplevel_handle_wm_capabilities,
};

//NOLINTBEGIN(*-easily-swappable-parameters)

void core::window::detail::WaylandWindowImpl::xdg_toplevel_handle_configure(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t              width,
    [[maybe_unused]] int32_t              height,
    [[maybe_unused]] struct wl_array*     states
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<WaylandWindowImpl*>(data);
}

void core::window::detail::WaylandWindowImpl::xdg_toplevel_handle_close(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel
) {
    auto* this_impl           = static_cast<WaylandWindowImpl*>(data);
    this_impl->m_should_close = true;
}

void core::window::detail::WaylandWindowImpl::
    xdg_toplevel_handle_configure_bounds(
        void*                                 data,
        [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
        [[maybe_unused]] int32_t              width,
        [[maybe_unused]] int32_t              height
    ) {
    [[maybe_unused]]
    auto* this_impl = static_cast<WaylandWindowImpl*>(data);
}

void core::window::detail::WaylandWindowImpl::
    xdg_toplevel_handle_wm_capabilities(
        void*                                 data,
        [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
        [[maybe_unused]] struct wl_array*     capabilities
    ) {
    [[maybe_unused]]
    auto* this_impl = static_cast<WaylandWindowImpl*>(data);
}

//NOLINTEND(*-easily-swappable-parameters)
