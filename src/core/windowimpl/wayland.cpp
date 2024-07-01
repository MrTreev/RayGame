#include "core/windowimpl/wayland.h" // IWYU pragma: keep
#include "core/logger.h"
#include <tuple>

void core::window::impl::wayland::buffer_release(
    void*             data,
    struct wl_buffer* wl_buffer
) {
    std::ignore = data;
    wl_buffer_destroy(wl_buffer);
}

void core::window::impl::wayland::registry_handle_global(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name,
    const char*         interface,
    uint32_t            version
) {
    auto* state = static_cast<core::WaylandWinState*>(data);
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        log::debug(interface);
        state->m_compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, version)
        );
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        log::debug(interface);
        state->m_shm = static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, version)
        );
    } else if (strcmp(interface, wl_shell_interface.name) == 0) {
        log::debug(interface);
        state->m_shell = static_cast<xdg_shell*>(
            wl_registry_bind(registry, name, &wl_shell_interface, version)
        );
    }
}

void core::window::impl::wayland::registry_handle_global_remove(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name
) {
    std::ignore = data;
    std::ignore = registry;
    log::debug(std::format("removing {}", name));
}

void core::window::impl::wayland::surface_enter_handler(
    void*              data,
    struct wl_surface* surface,
    struct wl_output*  output
) {
    std::ignore = data;
    std::ignore = output;
    log::debug(std::format("enter {}", static_cast<void*>(surface)));
}

void core::window::impl::wayland::surface_leave_handler(
    void*              data,
    struct wl_surface* surface,
    struct wl_output*  output
) {
    std::ignore = data;
    std::ignore = surface;
    std::ignore = output;
}

void core::window::impl::wayland::xdg_surface_configure(
    void*               data,
    struct xdg_surface* xdg_surface,
    uint32_t            serial
) {
    std::ignore = data;
    std::ignore = xdg_surface;
    std::ignore = serial;
}

void core::window::impl::wayland::xdg_toplevel_close_handler(
    void*                data,
    struct xdg_toplevel* xdg_toplevel
) {
    std::ignore = data;
    std::ignore = xdg_toplevel;
}

void core::window::impl::wayland::xdg_toplevel_configure_handler(
    void*                data,
    struct xdg_toplevel* xdg_toplevel,
    int32_t              width,
    int32_t              height,
    struct wl_array*     states
) {
    std::ignore = data;
    std::ignore = xdg_toplevel;
    std::ignore = width;
    std::ignore = height;
    std::ignore = states;
}
