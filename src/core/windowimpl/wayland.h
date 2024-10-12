#pragma once
#include "core/window.h"
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

namespace core::window {

class WaylandWindow: public Window<WaylandWindow> {
public:
    WaylandWindow(
        Vec2<size_t> size          = DEFAULT_WINDOW_SIZE,
        std::string  title         = DEFAULT_WINDOW_TITLE,
        WindowStyle  style         = DEFAULT_WINDOW_STYLE,
        bool         use_callbacks = true
    );
    ~WaylandWindow();
    void set_style(WindowStyle style);
    bool next_frame();
    void new_buffer(const Vec2<size_t>& size);
    void new_buffer();

private:
    struct axis_t {
        bool       valid;
        wl_fixed_t value;
        int32_t    discrete;
    };

    struct pointer_event {
        uint32_t   event_mask;
        wl_fixed_t surface_x, surface_y;
        uint32_t   button, state;
        uint32_t   time;
        uint32_t   serial;
        axis_t     axes[2];
        uint32_t   axis_source;
    };

    enum pointer_event_mask : uint32_t {
        POINTER_EVENT_ENTER         = 1 << 0,
        POINTER_EVENT_LEAVE         = 1 << 1,
        POINTER_EVENT_MOTION        = 1 << 2,
        POINTER_EVENT_BUTTON        = 1 << 3,
        POINTER_EVENT_AXIS          = 1 << 4,
        POINTER_EVENT_AXIS_SOURCE   = 1 << 5,
        POINTER_EVENT_AXIS_STOP     = 1 << 6,
        POINTER_EVENT_AXIS_DISCRETE = 1 << 7,
    };

    bool          m_configured = false;
    pointer_event m_pointer_event;
    uint32_t      m_last_frame = 0;

    wl_buffer*     m_wl_buffer     = nullptr;
    wl_callback*   m_wl_callback   = nullptr;
    wl_compositor* m_wl_compositor = nullptr;
    wl_display*    m_wl_display    = nullptr;
    wl_keyboard*   m_wl_keyboard   = nullptr;
    wl_pointer*    m_wl_pointer    = nullptr;
    wl_registry*   m_wl_registry   = nullptr;
    wl_seat*       m_wl_seat       = nullptr;
    wl_shm*        m_wl_shm        = nullptr;
    wl_surface*    m_wl_surface    = nullptr;
    xdg_surface*   m_xdg_surface   = nullptr;
    xdg_toplevel*  m_xdg_toplevel  = nullptr;
    xdg_wm_base*   m_xdg_wm_base   = nullptr;

    // clang-format off
    static void wl_pointer_handle_axis(void* data, wl_pointer* wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value);
    static void wl_pointer_handle_axis_discrete(void* data, wl_pointer* wl_pointer, uint32_t axis, int32_t discrete);
    static void wl_pointer_handle_axis_relative_direction( void* data, wl_pointer* wl_pointer, uint32_t axis, uint32_t direction);
    static void wl_pointer_handle_axis_source(void* data, wl_pointer* wl_pointer, uint32_t axis_source);
    static void wl_pointer_handle_axis_stop(void* data, wl_pointer* wl_pointer, uint32_t time, uint32_t axis);
    static void wl_pointer_handle_axis_value120(void* data, wl_pointer* wl_pointer, uint32_t axis, int32_t value120);
    static void wl_pointer_handle_button(void* data, wl_pointer* pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state);
    static void wl_pointer_handle_enter(void* data, wl_pointer* wl_pointer, uint32_t serial, wl_surface* surface, wl_fixed_t surface_x, wl_fixed_t surface_y);
    static void wl_pointer_handle_frame(void* data, wl_pointer* wl_pointer);
    static void wl_pointer_handle_leave(void* data, wl_pointer* wl_pointer, uint32_t serial, wl_surface* surface);
    static void wl_pointer_handle_motion(void* data, wl_pointer* wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y);
    static void wl_registry_handle_global(void* data, wl_registry* registry, uint32_t name, const char* interface, uint32_t version);
    static void wl_registry_handle_global_remove(void* data, wl_registry* registry, uint32_t name);
    static void wl_seat_handle_capabilities(void* data, wl_seat* seat, uint32_t capabilities);
    static void wl_seat_name(void* data, wl_seat* wl_seat, const char* name);
    static void wl_surface_draw_frame(void* data, wl_callback* wl_callback, uint32_t time);
    static void xdg_surface_handle_configure(void* data, xdg_surface* xdg_surface, uint32_t serial);
    static void xdg_wm_base_handle_ping(void* data, xdg_wm_base* xdg_wm_base, uint32_t serial);
    // clang-format on

    static const wl_callback_listener m_wl_surface_frame_listener;
    static const wl_pointer_listener  m_wl_pointer_listener;
    static const wl_registry_listener m_wl_registry_listener;
    static const wl_seat_listener     m_wl_seat_listener;
    static const xdg_surface_listener m_xdg_surface_listener;
    static const xdg_wm_base_listener m_xdg_wm_base_listener;
};

} // namespace core::window
