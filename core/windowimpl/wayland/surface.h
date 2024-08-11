#pragma once
#include "core/types.h"
#include "core/windowimpl/wayland/pixelbuffer.h"
#include <memory>
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

namespace core::window::wayland {

class Surface {
    using wl_del_t  = decltype(&wl_surface_destroy);
    using xdg_del_t = decltype(&xdg_surface_destroy);
    using top_del_t = decltype(&xdg_toplevel_destroy);
    std::unique_ptr<struct wl_surface>  m_wl_surface;
    std::unique_ptr<struct xdg_surface> m_xdg_surface;
    std::unique_ptr<struct xdg_surface> m_xdg_toplevel;

public:
    Surface() = delete;
    ~Surface();
    void damage(core::Vec2<size_t> origin, core::Vec2<size_t> size);
    void attach(const PixelBuffer& pixbuf);
    void commit();
};

} // namespace core::window::wayland
