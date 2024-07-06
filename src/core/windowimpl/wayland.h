#pragma once
#include "core/window.h" // IWYU pragma: keep
#include <cstring>
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

namespace core::window::wayland {
struct wl_buffer* create_buffer(
    const size_t& width,
    const size_t& height,
    const size_t& buffer_size
);

struct {
    struct wl_compositor* m_compositor{nullptr};
    struct wl_display*    m_display{nullptr};
    struct wl_registry*   m_registry{nullptr};
    struct wl_shm*        m_shm{nullptr};
    struct wl_surface*    m_surface{nullptr};
    struct xdg_toplevel*  m_xdg_toplevel{nullptr};
    struct xdg_wm_base*   m_xdg_wm_base{nullptr};
    void*                 m_shm_data{nullptr};
    bool                  m_configured = false;
    bool                  m_running    = true;
} wayland_state; //NOLINT
} // namespace core::window::wayland

namespace {
void xdg_wm_base_handle_ping(
    [[maybe_unused]] void*               data,
    [[maybe_unused]] struct xdg_wm_base* xdg_wm_base,
    [[maybe_unused]] uint32_t            serial
) {
    xdg_wm_base_pong(xdg_wm_base, serial);
}

const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_handle_ping,
};
} // namespace

namespace {
void xdg_surface_handle_configure(
    [[maybe_unused]] void*               data,
    [[maybe_unused]] struct xdg_surface* xdg_surface,
    [[maybe_unused]] uint32_t            serial
) {
    xdg_surface_ack_configure(xdg_surface, serial);
    if (core::window::wayland::wayland_state.m_configured) {
        wl_surface_commit(core::window::wayland::wayland_state.m_surface);
    }
    core::window::wayland::wayland_state.m_configured = true;
}

const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};
} // namespace

namespace {
void xdg_toplevel_handle_configure(
    [[maybe_unused]] void*                data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t              width,
    [[maybe_unused]] int32_t              height,
    [[maybe_unused]] struct wl_array*     states
) {}

void xdg_toplevel_handle_close(
    [[maybe_unused]] void*                data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel
) {
    core::window::wayland::wayland_state.m_running = false;
}

const struct xdg_toplevel_listener xdg_toplevel_listener = {
    .configure = xdg_toplevel_handle_configure,
    .close     = xdg_toplevel_handle_close,
};
} // namespace

namespace {
void pointer_handle_enter(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t           serial,
    [[maybe_unused]] struct wl_surface* surface,
    [[maybe_unused]] wl_fixed_t         surface_x,
    [[maybe_unused]] wl_fixed_t         surface_y
) {}

void pointer_handle_leave(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t           serial,
    [[maybe_unused]] struct wl_surface* surface
) {}

void pointer_handle_motion(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t           time,
    [[maybe_unused]] wl_fixed_t         surface_x,
    [[maybe_unused]] wl_fixed_t         surface_y
) {}

void pointer_handle_button(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* pointer,
    [[maybe_unused]] uint32_t           serial,
    [[maybe_unused]] uint32_t           time,
    [[maybe_unused]] uint32_t           button,
    [[maybe_unused]] uint32_t           state
) {
    auto* seat = static_cast<struct wl_seat*>(data);
    if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED) {
        xdg_toplevel_move(
            core::window::wayland::wayland_state.m_xdg_toplevel,
            seat,
            serial
        );
    }
}

void pointer_handle_axis(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t           time,
    [[maybe_unused]] uint32_t           axis,
    [[maybe_unused]] wl_fixed_t         value
) {}

const struct wl_pointer_listener pointer_listener = {
    .enter  = pointer_handle_enter,
    .leave  = pointer_handle_leave,
    .motion = pointer_handle_motion,
    .button = pointer_handle_button,
    .axis   = pointer_handle_axis,
};
} // namespace

namespace {
void seat_handle_capabilities(
    [[maybe_unused]] void*           data,
    [[maybe_unused]] struct wl_seat* seat,
    [[maybe_unused]] uint32_t        capabilities
) {
    // If the wl_seat has the pointer capability, start listening to pointer
    // events
    if ((capabilities & WL_SEAT_CAPABILITY_POINTER) != 0U) {
        struct wl_pointer* pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(pointer, &pointer_listener, seat);
    }
}
const struct wl_seat_listener seat_listener = {
    .capabilities = seat_handle_capabilities,
};
} // namespace

namespace {
void handle_global(
    [[maybe_unused]] void*               data,
    [[maybe_unused]] struct wl_registry* registry,
    [[maybe_unused]] uint32_t            name,
    [[maybe_unused]] const char*         interface,
    [[maybe_unused]] uint32_t            version
) {
    if (strcmp(interface, wl_shm_interface.name) == 0) {
        core::window::wayland::wayland_state.m_shm =
            static_cast<struct wl_shm*>(
                wl_registry_bind(registry, name, &wl_shm_interface, 1)
            );
    } else if (strcmp(interface, wl_seat_interface.name) == 0) {
        auto* seat = static_cast<struct wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface, 1)
        );
        wl_seat_add_listener(seat, &seat_listener, nullptr);
    } else if (strcmp(interface, wl_compositor_interface.name) == 0) {
        core::window::wayland::wayland_state.m_compositor =
            static_cast<struct wl_compositor*>(
                wl_registry_bind(registry, name, &wl_compositor_interface, 1)
            );
    } else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
        core::window::wayland::wayland_state.m_xdg_wm_base =
            static_cast<struct xdg_wm_base*>(
                wl_registry_bind(registry, name, &xdg_wm_base_interface, 1)
            );
        xdg_wm_base_add_listener(
            core::window::wayland::wayland_state.m_xdg_wm_base,
            &xdg_wm_base_listener,
            nullptr
        );
    }
}

void handle_global_remove(
    [[maybe_unused]] void*               data,
    [[maybe_unused]] struct wl_registry* registry,
    [[maybe_unused]] uint32_t            name
) {}

const struct wl_registry_listener registry_listener = {
    .global        = handle_global,
    .global_remove = handle_global_remove,
};

} // namespace
