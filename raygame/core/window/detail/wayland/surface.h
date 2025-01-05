#pragma once
#include "raygame/core/condition.h"
#include "raygame/core/math/vector.h"
#include "raygame/core/types.h"
#include <xdg-shell-client-protocol.h>

namespace core::window::detail {
class WaylandSurface {
    static constexpr size_t COLOUR_CHANNELS = 4;

    Vec2<size_t> m_size{0, 0};
    int          m_shm_fd{-1};
    uint32_t     m_last_frame{0};
    uint8_t*     m_pixel_buffer{nullptr};
    wl_buffer*   m_wl_buffer{nullptr};
    wl_shm*      m_wl_shm{nullptr};
    wl_shm_pool* m_wl_shm_pool{nullptr};
    wl_surface*  m_wl_surface{nullptr};
    xdg_surface* m_xdg_surface{nullptr};
    uint32_t     m_wl_shm_format{};

    static void
    configure(void* data, xdg_surface* xdg_surface, uint32_t serial);
    static void done(void* data, wl_callback* wl_callback, uint32_t time);
    void        new_buffer();

public:
    WaylandSurface();
    ~WaylandSurface();
    WaylandSurface(const WaylandSurface&)            = delete;
    WaylandSurface(WaylandSurface&&)                 = default;
    WaylandSurface& operator=(const WaylandSurface&) = delete;
    WaylandSurface& operator=(WaylandSurface&&)      = default;

    void bind_shm(wl_shm* shm) {
        condition::check_ptr(shm, "Cannot bind shm to nullptr");
        m_wl_shm = shm;
    }

    static const xdg_surface_listener m_xdg_listener;
    static const wl_callback_listener m_callback_listener;
};
} // namespace core::window::detail
