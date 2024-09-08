#include "core/condition.h"
#include "core/math.h"
#include "core/windowimpl/wayland.h"
#include "core/windowimpl/wayland/util.h"
#include <sys/mman.h>
#include <unistd.h>

using core::condition::check_condition;
using core::condition::check_ptr;
using core::math::numeric_cast;

static constexpr size_t COLOUR_CHANNELS = 4;

namespace core::window::wayland {

wl_compositor* WaylandWindow::m_compositor  = nullptr;
wl_display*    WaylandWindow::m_display     = nullptr;
wl_registry*   WaylandWindow::m_registry    = nullptr;
wl_shm*        WaylandWindow::m_shm         = nullptr;
xdg_wm_base*   WaylandWindow::m_xdg_wm_base = nullptr;
wl_seat*       WaylandWindow::m_wl_seat     = nullptr;

WaylandWindow::WaylandWindow(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : m_size(size) {
    if (m_display == nullptr) {
        m_display = wl_display_connect(nullptr);
        check_ptr(m_display, "Display setup failed");
        m_registry = wl_display_get_registry(m_display);
        check_ptr(m_registry, "Registry setup failed");
        wl_registry_add_listener(m_registry, &m_registry_listener, nullptr);
        check_condition(
            wl_display_roundtrip(m_display) != 0,
            "Display roundtrip failed"
        );
        check_ptr(m_shm, "shm global setup failed");
        check_ptr(m_compositor, "compositor global setup failed");
        check_ptr(m_xdg_wm_base, "xdg_wm_base global setup failed");
    }
    m_surface = wl_compositor_create_surface(m_compositor);
    check_ptr(m_surface, "wl_surface setup failed");
    m_xdg_surface = xdg_wm_base_get_xdg_surface(m_xdg_wm_base, m_surface);
    check_ptr(m_xdg_surface, "xdg_surface setup failed");
    xdg_surface_add_listener(m_xdg_surface, &m_xdg_surface_listener, nullptr);
    wl_surface_commit(m_surface);
    while (wl_display_dispatch(m_display) != -1) {
        log::error("Wayland display not configured");
    }
    xdg_toplevel_set_title(m_xdg_toplevel, title.c_str());
    new_buffer();
    set_style(style);
    wl_surface_attach(m_surface, m_buffer, 0, 0);
    wl_surface_commit(m_surface);
}

WaylandWindow::~WaylandWindow() {
    wl_buffer_destroy(m_buffer);
    wl_surface_destroy(m_surface);
    xdg_surface_destroy(m_xdg_surface);
    xdg_toplevel_destroy(m_xdg_toplevel);
}

void WaylandWindow::new_buffer(Vec2<size_t> size) {
    const size_t buflen  = numeric_cast<size_t>(size.x * size.y);
    const size_t bufsize = numeric_cast<size_t>(buflen * COLOUR_CHANNELS);
    const int    shm_fd  = allocate_shm_file(bufsize);
    check_condition(shm_fd >= 0, "creation of shm buffer file failed");
    auto shm_data =
        mmap(nullptr, bufsize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_data == MAP_FAILED) {
        close(shm_fd);
        check_condition(false, "Could not setup shm data");
    }
    wl_shm_pool* pool =
        wl_shm_create_pool(m_shm, shm_fd, numeric_cast<int32_t>(bufsize));
    m_buffer = wl_shm_pool_create_buffer(
        pool,
        0,
        numeric_cast<int32_t>(size.x),
        numeric_cast<int32_t>(size.y),
        numeric_cast<int32_t>(size.x * COLOUR_CHANNELS),
        get_colour_format()
    );
    wl_shm_pool_destroy(pool);
    close(shm_fd);
    check_ptr(m_buffer, "Failed to create buffer");
}

void WaylandWindow::set_style(WindowStyle style) {
    switch (style) {
    case WindowStyle::Windowed:
        xdg_toplevel_unset_fullscreen(m_xdg_toplevel);
        xdg_toplevel_unset_maximized(m_xdg_toplevel);
        break;
    case WindowStyle::WindowedFullscreen:
        xdg_toplevel_unset_fullscreen(m_xdg_toplevel);
        xdg_toplevel_set_maximized(m_xdg_toplevel);
        break;
    case WindowStyle::Fullscreen:
        xdg_toplevel_set_fullscreen(m_xdg_toplevel, nullptr);
        break;
    }
}

bool WaylandWindow::should_close() {
    return m_should_close;
}

} // namespace core::window::wayland
