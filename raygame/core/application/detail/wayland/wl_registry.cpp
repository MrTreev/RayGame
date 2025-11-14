#include "raygame/core/application/detail/wayland.h"
#include "raygame/core/logger.h"
#include "raygame/core/types.h"
#include <string>
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

const wl_registry_listener core::detail::AppImplWayland::m_wl_registry_listener = {
    .global        = wl_registry_handle_global,
    .global_remove = wl_registry_handle_global_remove,
};

void core::detail::AppImplWayland::wl_registry_handle_global(
    void*        data,
    wl_registry* registry,
    uint32_t     name,
    const char*  interface,
    uint32_t     version
) {
    auto*             this_impl = static_cast<AppImplWayland*>(data);
    const std::string interface_str{interface};
    if (interface_str == wl_shm_interface.name) {
        core::log::trace("Handled Global: {}", interface);
        this_impl->m_wl_shm =
            static_cast<wl_shm*>(wl_registry_bind(registry, name, &wl_shm_interface, version));
    } else if (interface_str == wl_compositor_interface.name) {
        core::log::trace("Handled Global: {}", interface);
        this_impl->m_wl_compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, version)
        );
    } else if (interface_str == xdg_wm_base_interface.name) {
        core::log::trace("Handled Global: {}", interface);
        this_impl->m_xdg_wm_base = static_cast<xdg_wm_base*>(
            wl_registry_bind(registry, name, &xdg_wm_base_interface, version)
        );
        xdg_wm_base_add_listener(this_impl->m_xdg_wm_base, &m_xdg_wm_base_listener, this_impl);
    } else if (interface_str == wl_seat_interface.name) {
        core::log::trace("Handled Global: {}", interface);
        this_impl->m_wl_seat =
            static_cast<wl_seat*>(wl_registry_bind(registry, name, &wl_seat_interface, version));
        wl_seat_add_listener(this_impl->m_wl_seat, &m_wl_seat_listener, this_impl);
    } else {
        core::log::trace("Unhandled Global: {}", interface);
    }
}

void core::detail::AppImplWayland::wl_registry_handle_global_remove(
    void*        data,
    wl_registry* registry,
    uint32_t     name
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<AppImplWayland*>(data);
    wl_registry_destroy(registry);
    core::log::trace("removed registry: {}", name);
}
