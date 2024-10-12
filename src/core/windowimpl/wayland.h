#pragma once
#include "core/window.h"
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

namespace core::window::wayland {

class WaylandWindow: public Window {
public:
    WaylandWindow(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    ~WaylandWindow();
    WaylandWindow(WaylandWindow&)             = delete;
    WaylandWindow(WaylandWindow&&)            = delete;
    WaylandWindow  operator=(WaylandWindow&)  = delete;
    WaylandWindow& operator=(WaylandWindow&&) = delete;

    void set_style(WindowStyle style);
    void new_buffer(Vec2<size_t> size);
    bool should_close();

    inline void new_buffer() {
        new_buffer(m_size);
    }

private:
    static wl_compositor* m_compositor;
    static wl_display*    m_display;
    static wl_registry*   m_registry;
    static wl_shm*        m_shm;
    static xdg_wm_base*   m_xdg_wm_base;
    static wl_seat*       m_wl_seat;

    static const wl_pointer_listener  m_wl_pointer_listener;
    static const wl_registry_listener m_registry_listener;
    static const wl_seat_listener     m_wl_seat_listener;
    static const xdg_wm_base_listener m_xdg_wm_base_listener;

    wl_buffer*    m_buffer       = nullptr;
    wl_surface*   m_surface      = nullptr;
    xdg_surface*  m_xdg_surface  = nullptr;
    xdg_toplevel* m_xdg_toplevel = nullptr;

    static const xdg_surface_listener m_xdg_surface_listener;

    static void registry_handle_global(
        void*        data,
        wl_registry* registry,
        uint32_t     name,
        const char*  interface,
        uint32_t     version
    );

    static void wl_seat_handle_capabilities(
        void*    data,
        wl_seat* seat,
        uint32_t capabilities
    );
};

} // namespace core::window::wayland
