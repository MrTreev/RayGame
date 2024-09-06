#include "core/logger.h"
#include "core/windowimpl/wayland.h" // IWYU pragma: keep
#include <format>
#include <linux/input-event-codes.h>
#include <wayland-protocol.h>
#include <xdg-shell-protocol.h>

namespace {

void rg_xdg_surface_handle_configure(
    void*        data,
    xdg_surface* xdg_surface,
    uint32_t     serial
) {
    std::ignore = data;
    xdg_surface_ack_configure(xdg_surface, serial);
}

void registry_handle_global_remove(
    void*        data,
    wl_registry* registry,
    uint32_t     name
) {
    std::ignore = data;
    wl_registry_destroy(registry);
    core::log::debug(std::format("remove registry: {}", name));
}

void xdg_wm_base_handle_ping(
    void*        data,
    xdg_wm_base* xdg_wm_base,
    uint32_t     serial
) {
    std::ignore = data;
    xdg_wm_base_pong(xdg_wm_base, serial);
}

void wl_pointer_handle_enter(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    serial,
    [[maybe_unused]] wl_surface* surface,
    [[maybe_unused]] wl_fixed_t  surface_x,
    [[maybe_unused]] wl_fixed_t  surface_y
) {}

void wl_pointer_handle_leave(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    serial,
    [[maybe_unused]] wl_surface* surface
) {}

void wl_pointer_handle_motion(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    time,
    [[maybe_unused]] wl_fixed_t  surface_x,
    [[maybe_unused]] wl_fixed_t  surface_y
) {}

void wl_pointer_handle_button(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* pointer,
    [[maybe_unused]] uint32_t    serial,
    [[maybe_unused]] uint32_t    time,
    [[maybe_unused]] uint32_t    button,
    [[maybe_unused]] uint32_t    state
) {}

void wl_pointer_handle_axis(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    time,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] wl_fixed_t  value
) {}

} // namespace

namespace core::window::wayland {

void WaylandWindow::registry_handle_global(
    void*        data,
    wl_registry* registry,
    uint32_t     name,
    const char*  interface,
    uint32_t     version
) {
    std::ignore = data;
    std::ignore = version;
    const std::string interface_str{interface};
    if (interface_str == wl_shm_interface.name) {
        core::log::debug(std::format("{}", interface));
        m_shm = static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, 1)
        );
    } else if (interface_str == wl_compositor_interface.name) {
        core::log::debug(std::format("{}", interface));
        m_compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, 1)
        );
    } else if (interface_str == xdg_wm_base_interface.name) {
        core::log::debug(std::format("{}", interface));
        m_xdg_wm_base = static_cast<xdg_wm_base*>(
            wl_registry_bind(registry, name, &xdg_wm_base_interface, 1)
        );
        xdg_wm_base_add_listener(
            m_xdg_wm_base,
            &m_xdg_wm_base_listener,
            nullptr
        );
    } else if (interface_str == wl_seat_interface.name) {
        core::log::debug(std::format("{}", interface));
        m_wl_seat = static_cast<wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface, 7)
        );
        wl_seat_add_listener(m_wl_seat, &m_wl_seat_listener, nullptr);
    } else {
        core::log::trace(std::format("Unhandled: {}", interface));
    }
}

void WaylandWindow::wl_seat_handle_capabilities(
    void*    data,
    wl_seat* seat,
    uint32_t capabilities
) {
    std::ignore = data;
    if ((capabilities & WL_SEAT_CAPABILITY_POINTER) != 0U) {
        wl_pointer* pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(pointer, &m_wl_pointer_listener, seat);
    }
}

const wl_registry_listener WaylandWindow::m_registry_listener = {
    .global        = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};

const xdg_wm_base_listener WaylandWindow::m_xdg_wm_base_listener = {
    .ping = xdg_wm_base_handle_ping,
};

const wl_seat_listener WaylandWindow::m_wl_seat_listener = {
    .capabilities = wl_seat_handle_capabilities,
    .name         = nullptr,
};

const wl_pointer_listener WaylandWindow::m_wl_pointer_listener = {
    .enter                   = wl_pointer_handle_enter,
    .leave                   = wl_pointer_handle_leave,
    .motion                  = wl_pointer_handle_motion,
    .button                  = wl_pointer_handle_button,
    .axis                    = wl_pointer_handle_axis,
    .frame                   = nullptr,
    .axis_source             = nullptr,
    .axis_stop               = nullptr,
    .axis_discrete           = nullptr,
    .axis_value120           = nullptr,
    .axis_relative_direction = nullptr,
};

const xdg_surface_listener WaylandWindow::m_xdg_surface_listener = {
    .configure = rg_xdg_surface_handle_configure,
};

} // namespace core::window::wayland
