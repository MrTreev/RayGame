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
    const size_t&            width,
    const size_t&            height,
    const size_t&            buffer_size,
    const std::string&       title,
    const core::WindowStyle& style
);

void destroy_window();

void render_frame(const size_t& width, const size_t& height);

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

extern const struct xdg_wm_base_listener xdg_wm_base_listener;

extern const struct xdg_surface_listener xdg_surface_listener;

extern const struct xdg_toplevel_listener xdg_toplevel_listener;

extern const struct wl_pointer_listener pointer_listener;

extern const struct wl_seat_listener seat_listener;

extern const struct wl_registry_listener registry_listener;
