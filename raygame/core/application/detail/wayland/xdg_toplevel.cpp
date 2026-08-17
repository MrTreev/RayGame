#include "raygame/core/application/detail/wayland.hpp"
#include "raygame/core/application/detail/wayland/wl_include.hpp"
#include "raygame/core/logger.hpp"
#include "raygame/core/math/numeric_cast.hpp"
#include "raygame/core/types.hpp"

const xdg_toplevel_listener core::detail::AppImplWayland::m_xdg_toplevel_listener = {
    .configure        = xdg_toplevel_handle_configure,
    .close            = xdg_toplevel_handle_close,
    .configure_bounds = xdg_toplevel_handle_configure_bounds,
    .wm_capabilities  = xdg_toplevel_handle_wm_capabilities,
};

//NOLINTBEGIN(*-easily-swappable-parameters)

void core::detail::AppImplWayland::xdg_toplevel_handle_configure(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    int32_t                               width,
    int32_t                               height,
    [[maybe_unused]] struct wl_array*     states
) {
    auto* this_impl = static_cast<AppImplWayland*>(data);
    if (width == 0 || height == 0) {
        return;
    }
    log::debug("Configure: width={}, height={}", width, height);
    this_impl->set_size({math::numeric_cast<size_t>(width), math::numeric_cast<size_t>(height)});
    this_impl->recreate_buffers();
}

void core::detail::AppImplWayland::xdg_toplevel_handle_close(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel
) {
    auto* this_impl           = static_cast<AppImplWayland*>(data);
    this_impl->m_should_close = true;
}

void core::detail::AppImplWayland::xdg_toplevel_handle_configure_bounds(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    int32_t                               width,
    int32_t                               height
) {
    auto* this_impl = static_cast<AppImplWayland*>(data);
    log::debug("Configure Bounds: {}, {}", width, height);
    this_impl->set_size({math::numeric_cast<size_t>(width), math::numeric_cast<size_t>(height)});
    this_impl->recreate_buffers();
}

void core::detail::AppImplWayland::xdg_toplevel_handle_wm_capabilities(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] struct wl_array*     capabilities
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<AppImplWayland*>(data);
}

//NOLINTEND(*-easily-swappable-parameters)
