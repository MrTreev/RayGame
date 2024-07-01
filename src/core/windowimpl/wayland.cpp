#include "core/windowimpl/wayland.h" // IWYU pragma: keep
#include "core/logger.h"

// after all else
#include "core/windowimpl/wayland/xdg-shell.h"

void core::window::impl::wayland::buffer_release(
    void*             data,
    struct wl_buffer* wl_buffer
) {
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
            wl_registry_bind(registry, name, &wl_compositor_interface, 3)
        );
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        log::debug(interface);
        state->m_shm = static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, 1)
        );
    } else if (strcmp(interface, zxdg_shell_v6_interface.name) == 0) {
        log::debug(interface);
        state->m_shell = static_cast<zxdg_shell_v6*>(
            wl_registry_bind(registry, name, &zxdg_shell_v6_interface, 1)
        );
    }
}

void core::window::impl::wayland::registry_handle_global_remove(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name
) {
    // Left Blank
}

void core::window::impl::wayland::surface_enter_handler(
    void*              data,
    struct wl_surface* surface,
    struct wl_output*  output
) {}

void core::window::impl::wayland::surface_leave_handler(
    void*              data,
    struct wl_surface* surface,
    struct wl_output*  output
) {}

void core::window::impl::wayland::xdg_surface_configure(
    void*                   data,
    struct zxdg_surface_v6* xdg_surface,
    uint32_t                serial
) {
    zxdg_surface_v6_ack_configure(xdg_surface, serial);
}

void core::window::impl::wayland::xdg_toplevel_close_handler(
    void*                    data,
    struct zxdg_toplevel_v6* xdg_toplevel
) {}

void core::window::impl::wayland::xdg_toplevel_configure_handler(
    void*                    data,
    struct zxdg_toplevel_v6* xdg_toplevel,
    int32_t                  width,
    int32_t                  height,
    struct wl_array*         states
) {}
