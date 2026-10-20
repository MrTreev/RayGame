#include "raygame/core/application/detail/wayland.hpp"
#include "raygame/core/application/detail/wayland/wl_include.hpp"
#include "raygame/core/logger.hpp"
#include "raygame/core/types.hpp"
#include <string>

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
    auto* this_impl = static_cast<AppImplWayland*>(data);
    if (this_impl->m_should_close) {
        return;
    }
    const std::string interface_str{interface};
    if (interface_str == wl_shm_interface.name) {
        this_impl->m_wl_shm_name = name;
        core::log::trace("Handled Global: {}", interface);
        this_impl->m_wl_shm =
            static_cast<wl_shm*>(wl_registry_bind(registry, name, &wl_shm_interface, version));
    } else if (interface_str == wl_compositor_interface.name) {
        this_impl->m_wl_compositor_name = name;
        core::log::trace("Handled Global: {}", interface);
        this_impl->m_wl_compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, version)
        );
    } else if (interface_str == xdg_wm_base_interface.name) {
        this_impl->m_xdg_wm_base_name = name;
        core::log::trace("Handled Global: {}", interface);
        this_impl->m_xdg_wm_base = static_cast<xdg_wm_base*>(
            wl_registry_bind(registry, name, &xdg_wm_base_interface, version)
        );
        xdg_wm_base_add_listener(this_impl->m_xdg_wm_base, &m_xdg_wm_base_listener, this_impl);
    } else if (interface_str == wl_seat_interface.name) {
        this_impl->m_wl_seat_name = name;
        core::log::trace("Handled Global: {}", interface);
        this_impl->m_wl_seat =
            static_cast<wl_seat*>(wl_registry_bind(registry, name, &wl_seat_interface, version));
        wl_seat_add_listener(this_impl->m_wl_seat, &m_wl_seat_listener, this_impl);
    } else {
        core::log::trace("Unhandled Global: {}", interface);
    }
}

void core::detail::AppImplWayland::wl_registry_handle_global_remove(
    void*                         data,
    [[maybe_unused]] wl_registry* registry,
    uint32_t                      name
) {
    auto* this_impl = static_cast<AppImplWayland*>(data);
    if (this_impl->m_should_close) {
        return;
    }
    if (name == this_impl->m_wl_shm_name && (this_impl->m_wl_shm != nullptr)) {
        wl_shm_destroy(this_impl->m_wl_shm);
        this_impl->m_wl_shm      = nullptr;
        this_impl->m_wl_shm_name = 0;
        core::log::info("wl_shm removed");
    } else if (name == this_impl->m_wl_compositor_name && (this_impl->m_wl_compositor != nullptr)) {
        wl_compositor_destroy(this_impl->m_wl_compositor);
        this_impl->m_wl_compositor      = nullptr;
        this_impl->m_wl_compositor_name = 0;
        core::log::warning("wl_compositor removed");
        this_impl->set_close();
    } else if (name == this_impl->m_xdg_wm_base_name && (this_impl->m_xdg_wm_base != nullptr)) {
        xdg_wm_base_destroy(this_impl->m_xdg_wm_base);
        this_impl->m_xdg_wm_base      = nullptr;
        this_impl->m_xdg_wm_base_name = 0;
        core::log::warning("xdg_wm_base removed");
        this_impl->set_close();
    } else if (name == this_impl->m_wl_seat_name && (this_impl->m_wl_seat != nullptr)) {
        // Also release any devices obtained from the seat
        if (this_impl->m_wl_pointer != nullptr) {
            wl_pointer_release(this_impl->m_wl_pointer);
            this_impl->m_wl_pointer = nullptr;
        }
        if (this_impl->m_wl_keyboard != nullptr) {
            wl_keyboard_release(this_impl->m_wl_keyboard);
            this_impl->m_wl_keyboard = nullptr;
        }
        wl_seat_release(this_impl->m_wl_seat);
        this_impl->m_wl_seat      = nullptr;
        this_impl->m_wl_seat_name = 0;
        log::warning("wl_seat removed");
    }
}
