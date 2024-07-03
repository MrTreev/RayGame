#pragma once
#include "core/window.h" // IWYU pragma: keep
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>
#include <xdg-shell.h>

namespace core {
struct WaylandWinState {
    std::string m_title{};
    size_t      m_width{0};
    size_t      m_height{0};
    size_t      m_buffer_size{0};
};
} // namespace core

namespace core::window::wayland {} // namespace core::window::wayland

namespace {
struct {
    bool               m_configured = false;
    struct wl_surface* m_surface    = nullptr;
} wayland_state; //NOLINT

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
    // The compositor configures our surface, acknowledge the configure event
    xdg_surface_ack_configure(xdg_surface, serial);

    if (wayland_state.m_configured) {
        // If this isn't the first configure event we've received, we already
        // have a buffer attached, so no need to do anything. Commit the
        // surface to apply the configure acknowledgement.
        wl_surface_commit(wayland_state.m_surface);
    }

    wayland_state.m_configured = true;
}
const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};
} // namespace

namespace {
void xdg_toplevel_handle_configure(
    void*                data,
    struct xdg_toplevel* xdg_toplevel,
    int32_t              width,
    int32_t              height,
    struct wl_array*     states
) {}
const struct xdg_toplevel_listener xdg_toplevel_listener = {
    .configure = xdg_toplevel_handle_configure,
    .close     = xdg_toplevel_handle_close,
};

const struct wl_pointer_listener pointer_listener = {
    .enter  = []() {},
    .leave  = []() {},
    .motion = []() {},
    .button = pointer_handle_button,
    .axis   = []() {},
};

const struct wl_seat_listener seat_listener = {
    .capabilities = seat_handle_capabilities,
};

const struct wl_registry_listener registry_listener = {
    .global        = handle_global,
    .global_remove = handle_global_remove,
};

} // namespace
