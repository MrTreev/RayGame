#pragma once
#include "core/types.h"
#include <memory>
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

namespace core::window::wayland {

class Region;
class Surface;
class PixelBuffer;

class WaylandWindow {
    using reg_del_t = decltype(&wl_compositor_destroy);
    using com_del_t = decltype(&wl_registry_destroy);
    using shm_del_t = decltype(&wl_shm_destroy);
    static std::unique_ptr<struct wl_compositor, com_del_t> m_compositor;
    static std::unique_ptr<struct wl_display>               m_display;
    static std::unique_ptr<struct wl_registry, reg_del_t>   m_registry;
    static std::unique_ptr<struct wl_shm, shm_del_t>        m_shm;

public:
    WaylandWindow();
    ~WaylandWindow();
    static void        add_listener();
    static void        roundtrip();
    static Surface     create_surface();
    static Region      create_region(const core::Rect<size_t>& rect);
    static PixelBuffer create_buffer(const core::Vec2<size_t>& size);
};

} // namespace core::window::wayland
