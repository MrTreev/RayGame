#pragma once
#include "core/logger.h"
#include "core/window.h" // IWYU pragma: keep
#include <cstring>
#include <format>
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

namespace {
constexpr size_t COLOUR_CHANNELS = 4;
constexpr size_t N_BUFFERS       = 2;
} // namespace

namespace core::window::wayland {
struct wl_buffer* create_buffer(
    const size_t& width,
    const size_t& height,
    const size_t& buffer_size
);

void init_window(
    const size_t&      width,
    const size_t&      height,
    const size_t&      buffer_size,
    const std::string& title
);

void destroy_window();

void render_frame();

struct wl_state_t {
    struct wl_compositor* m_compositor;
    struct wl_display*    m_display;
    struct wl_registry*   m_registry;
    struct wl_shm*        m_shm;
    struct wl_surface*    m_surface;
    struct xdg_toplevel*  m_xdg_toplevel;
    struct xdg_surface*   m_xdg_surface;
    struct xdg_wm_base*   m_xdg_wm_base;
    void*                 m_shm_data;
    bool                  m_configured;
    bool                  m_running;
    struct wl_buffer*     m_buffer;
};

extern wl_state_t wayland_state; // NOLINT: -avoid-non-const-global-variables
} // namespace core::window::wayland

namespace {
void xdg_wm_base_handle_ping(
    [[maybe_unused]] void*               data,
    [[maybe_unused]] struct xdg_wm_base* xdg_wm_base,
    [[maybe_unused]] uint32_t            serial
) {
    xdg_wm_base_pong(xdg_wm_base, serial);
}
} // namespace

static const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_handle_ping,
};

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
} // namespace

static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};

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
} // namespace

static const struct xdg_toplevel_listener xdg_toplevel_listener = {
    .configure = xdg_toplevel_handle_configure,
    .close     = xdg_toplevel_handle_close,
};

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
} // namespace

static const struct wl_pointer_listener pointer_listener = {
    .enter  = pointer_handle_enter,
    .leave  = pointer_handle_leave,
    .motion = pointer_handle_motion,
    .button = pointer_handle_button,
    .axis   = pointer_handle_axis,
};

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
} // namespace

static const struct wl_seat_listener seat_listener = {
    .capabilities = seat_handle_capabilities,
};

namespace {
void handle_global(
    [[maybe_unused]] void*               data,
    [[maybe_unused]] struct wl_registry* registry,
    [[maybe_unused]] uint32_t            name,
    [[maybe_unused]] const char*         interface,
    [[maybe_unused]] uint32_t            version
) {
    core::log::debug(std::format("{}", interface));
    if (strcmp(interface, wl_shm_interface.name) == 0) {
        core::log::debug("Handling SHM");
        core::log::debug(std::format("{}", size_t(registry)));
        core::window::wayland::wayland_state.m_shm =
            static_cast<struct wl_shm*>(
                wl_registry_bind(registry, name, &wl_shm_interface, 1)
            );
        core::log::debug(std::format(
            "{}",
            size_t(core::window::wayland::wayland_state.m_shm)
        ));
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
} // namespace

static const struct wl_registry_listener registry_listener = {
    .global        = handle_global,
    .global_remove = handle_global_remove,
};
