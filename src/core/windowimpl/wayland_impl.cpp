#include "core/logger.h"
#include "core/math.h"
#include "core/windowimpl/wayland.h"
#include <format>
#include <linux/input-event-codes.h>
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

void core::window::WaylandWindow::wl_pointer_handle_axis(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis,
    wl_fixed_t                   value
) {
    core::log::trace(std::format("{}: {}, {}", time, axis, value));
}

void core::window::WaylandWindow::wl_pointer_handle_axis_discrete(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] int32_t     discrete
) {
    core::log::trace(std::format("{}, {}", axis, discrete));
}

void core::window::WaylandWindow::wl_pointer_handle_axis_relative_direction(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis,
    uint32_t                     direction
) {
    core::log::trace(std::format("{}, {}", axis, direction));
}

void core::window::WaylandWindow::wl_pointer_handle_axis_source(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis_source
) {
    core::log::trace(std::format("{}", axis_source));
}

void core::window::WaylandWindow::wl_pointer_handle_axis_stop(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis
) {
    core::log::trace(std::format("{}, {}", time, axis));
}

void core::window::WaylandWindow::wl_pointer_handle_axis_value120(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis,
    int32_t                      value120
) {
    core::log::trace(std::format("{}, {}", axis, value120));
}

void core::window::WaylandWindow::wl_pointer_handle_button(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* pointer,
    [[maybe_unused]] uint32_t    serial,
    uint32_t                     time,
    uint32_t                     button,
    uint32_t                     state
) {
    core::log::trace(std::format("{}: {}, {}", time, button, state));
}

void core::window::WaylandWindow::wl_pointer_handle_enter(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     serial,
    wl_surface*                  surface,
    wl_fixed_t                   surface_x,
    wl_fixed_t                   surface_y
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    core::log::trace(std::format("({}, {})", surface_x, surface_y));
    thiswindow->m_pointer_event.event_mask |= POINTER_EVENT_ENTER;
    thiswindow->m_pointer_event.serial      = serial;
    thiswindow->m_pointer_event.surface_x   = surface_x,
    thiswindow->m_pointer_event.surface_y   = surface_y;
}

void core::window::WaylandWindow::wl_pointer_handle_frame(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer
) {}

void core::window::WaylandWindow::wl_pointer_handle_leave(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     serial,
    [[maybe_unused]] wl_surface* surface
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    core::log::trace(std::format(""));
    thiswindow->m_pointer_event.serial      = serial;
    thiswindow->m_pointer_event.event_mask |= POINTER_EVENT_LEAVE;
}

void core::window::WaylandWindow::wl_pointer_handle_motion(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    wl_fixed_t                   surface_x,
    wl_fixed_t                   surface_y
) {
    core::log::trace(std::format("{}: ({}, {})", time, surface_x, surface_y));
}

void core::window::WaylandWindow::wl_registry_handle_global(
    void*        data,
    wl_registry* registry,
    uint32_t     name,
    const char*  interface,
    uint32_t     version
) {
    WaylandWindow*    thiswindow = static_cast<WaylandWindow*>(data);
    const std::string interface_str{interface};
    if (interface_str == wl_shm_interface.name) {
        core::log::trace(std::format("{}", interface));
        thiswindow->m_wl_shm = static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, version)
        );
    } else if (interface_str == wl_compositor_interface.name) {
        core::log::trace(std::format("{}", interface));
        thiswindow->m_wl_compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, version)
        );
    } else if (interface_str == xdg_wm_base_interface.name) {
        core::log::trace(std::format("{}", interface));
        thiswindow->m_xdg_wm_base = static_cast<xdg_wm_base*>(
            wl_registry_bind(registry, name, &xdg_wm_base_interface, version)
        );
        xdg_wm_base_add_listener(
            thiswindow->m_xdg_wm_base,
            &m_xdg_wm_base_listener,
            thiswindow
        );
    } else if (interface_str == wl_seat_interface.name) {
        core::log::trace(std::format("{}", interface));
        thiswindow->m_wl_seat = static_cast<wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface, version)
        );
        wl_seat_add_listener(
            thiswindow->m_wl_seat,
            &m_wl_seat_listener,
            thiswindow
        );
    } else {
        core::log::trace(std::format("Unhandled: {}", interface));
    }
}

void core::window::WaylandWindow::wl_registry_handle_global_remove(
    [[maybe_unused]] void* data,
    wl_registry*           registry,
    uint32_t               name
) {
    wl_registry_destroy(registry);
    core::log::trace(std::format("remove registry: {}", name));
}

void core::window::WaylandWindow::wl_seat_handle_capabilities(
    void*    data,
    wl_seat* seat,
    uint32_t capabilities
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    bool have_pointer = (capabilities != 0U) && WL_SEAT_CAPABILITY_POINTER;
    if (have_pointer && thiswindow->m_wl_pointer == nullptr) {
        thiswindow->m_wl_pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(
            thiswindow->m_wl_pointer,
            &m_wl_pointer_listener,
            thiswindow
        );
    } else if (!have_pointer && thiswindow->m_wl_pointer != nullptr) {
        wl_pointer_release(thiswindow->m_wl_pointer);
        thiswindow->m_wl_pointer = nullptr;
    }
}

void core::window::WaylandWindow::wl_seat_name(
    [[maybe_unused]] void*    data,
    [[maybe_unused]] wl_seat* wl_seat,
    const char*               name
) {
    core::log::trace(std::format("{}", name));
}

void core::window::WaylandWindow::wl_surface_draw_frame(
    void*        data,
    wl_callback* wl_callback,
    uint32_t     time
) {
    using core::math::numeric_cast;
    wl_callback_destroy(wl_callback);
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    wl_callback               = wl_surface_frame(thiswindow->m_wl_surface);
    wl_callback_add_listener(
        wl_callback,
        &m_wl_surface_frame_listener,
        thiswindow
    );
    thiswindow->new_buffer();
    wl_surface_attach(thiswindow->m_wl_surface, thiswindow->m_wl_buffer, 0, 0);
    wl_surface_damage_buffer(
        thiswindow->m_wl_surface,
        0,
        0,
        numeric_cast<int32_t>(thiswindow->m_size.x),
        numeric_cast<int32_t>(thiswindow->m_size.y)
    );
    wl_surface_commit(thiswindow->m_wl_surface);
    thiswindow->m_last_frame = time;
}

void core::window::WaylandWindow::xdg_surface_handle_configure(
    void*        data,
    xdg_surface* xdg_surface,
    uint32_t     serial
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    xdg_surface_ack_configure(xdg_surface, serial);
    if (thiswindow->m_configured) {
        wl_surface_commit(thiswindow->m_wl_surface);
    }
    thiswindow->m_configured = true;
}

void core::window::WaylandWindow::xdg_wm_base_handle_ping(
    [[maybe_unused]] void* data,
    xdg_wm_base*           xdg_wm_base,
    uint32_t               serial
) {
    xdg_wm_base_pong(xdg_wm_base, serial);
}

const wl_callback_listener
    core::window::WaylandWindow::m_wl_surface_frame_listener{
        .done = wl_surface_draw_frame,
    };

const wl_pointer_listener core::window::WaylandWindow::m_wl_pointer_listener = {
    .enter                   = wl_pointer_handle_enter,
    .leave                   = wl_pointer_handle_leave,
    .motion                  = wl_pointer_handle_motion,
    .button                  = wl_pointer_handle_button,
    .axis                    = wl_pointer_handle_axis,
    .frame                   = wl_pointer_handle_frame,
    .axis_source             = wl_pointer_handle_axis_source,
    .axis_stop               = wl_pointer_handle_axis_stop,
    .axis_discrete           = wl_pointer_handle_axis_discrete,
    .axis_value120           = wl_pointer_handle_axis_value120,
    .axis_relative_direction = wl_pointer_handle_axis_relative_direction,
};

const wl_registry_listener core::window::WaylandWindow::m_wl_registry_listener =
    {
        .global        = wl_registry_handle_global,
        .global_remove = wl_registry_handle_global_remove,
};

const wl_seat_listener core::window::WaylandWindow::m_wl_seat_listener = {
    .capabilities = wl_seat_handle_capabilities,
    .name         = wl_seat_name,
};

const xdg_surface_listener core::window::WaylandWindow::m_xdg_surface_listener =
    {
        .configure = xdg_surface_handle_configure,
};

const xdg_wm_base_listener core::window::WaylandWindow::m_xdg_wm_base_listener =
    {
        .ping = xdg_wm_base_handle_ping,
};
