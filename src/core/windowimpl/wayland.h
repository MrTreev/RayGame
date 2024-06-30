#pragma once
#include "core/window.h" // IWYU pragma: keep
#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <wayland-client.h>

// after client
#include "core/windowimpl/wayland/xdg-shell.h"

namespace core {

struct WaylandWinState {
    std::string              m_title{};
    size_t                   m_width{0};
    size_t                   m_height{0};
    size_t                   m_buffer_size{0};
    int                      m_shm_fd{0};
    /* Globals */
    struct wl_display*       m_display{nullptr};
    struct wl_registry*      m_registry{nullptr};
    struct wl_shm*           m_shm{nullptr};
    struct wl_compositor*    m_compositor{nullptr};
    /* Objects */
    struct wl_surface*       m_surface{nullptr};
    struct zxdg_shell_v6*    m_shell{nullptr};
    struct zxdg_surface_v6*  m_xdg_surface{nullptr};
    struct zxdg_toplevel_v6* m_xdg_toplevel{nullptr};
    struct wl_shm_pool*      m_pool{nullptr};
    struct wl_buffer*        m_buffer{nullptr};
};

namespace window::impl::wayland {

void registry_handle_global(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name,
    const char*         interface,
    uint32_t            version
);

void registry_handle_global_remove(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name
);

void buffer_release(void* data, struct wl_buffer* wl_buffer);

void surface_enter_handler(
    void*              data,
    struct wl_surface* surface,
    struct wl_output*  output
);

void surface_leave_handler(
    void*              data,
    struct wl_surface* surface,
    struct wl_output*  output
);

void xdg_surface_configure(
    void*                   data,
    struct zxdg_surface_v6* xdg_surface,
    uint32_t                serial
);

void xdg_toplevel_close_handler(
    void*                    data,
    struct zxdg_toplevel_v6* xdg_toplevel
);

void xdg_toplevel_configure_handler(
    void*                    data,
    struct zxdg_toplevel_v6* xdg_toplevel,
    int32_t                  width,
    int32_t                  height,
    struct wl_array*         states
);

} // namespace window::impl::wayland
} // namespace core
