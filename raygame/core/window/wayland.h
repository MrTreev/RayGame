#pragma once
#include "raygame/core/window/window.h"

struct wl_array;
struct wl_buffer;
struct wl_callback;
struct wl_callback_listener;
struct wl_compositor;
struct wl_display;
struct wl_keyboard;
struct wl_keyboard_listener;
struct wl_pointer;
struct wl_pointer_listener;
struct wl_registry;
struct wl_registry_listener;
struct wl_seat;
struct wl_seat_listener;
struct wl_shm;
struct wl_surface;
struct xdg_surface;
struct xdg_surface_listener;
struct xdg_toplevel;
struct xdg_toplevel_listener;
struct xdg_wm_base;
struct xdg_wm_base_listener;
struct xkb_context;
struct xkb_keymap;
struct xkb_state;

namespace core::window {
class WaylandWindow;

namespace detail {

class WaylandImpl {
    using wl_fixed_t = int32_t;

    struct axis_t {
        bool       valid;
        wl_fixed_t value;
        int32_t    discrete;
    };

    struct pointer_event {
        uint32_t   event_mask;
        wl_fixed_t surface_x;
        wl_fixed_t surface_y;
        uint32_t   button;
        uint32_t   state;
        uint32_t   time;
        uint32_t   serial;
        axis_t     axis_vertical;
        axis_t     axis_horizontal;
        uint32_t   axis_source;
    };

    struct keyboard_state {
        keyboard_state();
        keyboard_state(const keyboard_state&)            = default;
        keyboard_state(keyboard_state&&)                 = default;
        keyboard_state& operator=(const keyboard_state&) = default;
        keyboard_state& operator=(keyboard_state&&)      = default;
        ~keyboard_state();

        //NOLINTBEGIN(*-non-private-member-*)
        xkb_state*   m_xkb_state   = nullptr;
        xkb_keymap*  m_xkb_keymap  = nullptr;
        xkb_context* m_xkb_context = nullptr;
        //NOLINTEND(*-non-private-member-*)
    };

    WaylandWindow* m_base;
    bool           m_configured = false;
    uint32_t       m_last_frame = 0;
    pointer_event  m_pointer_event{};
    keyboard_state m_keyboard_state;

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
    static void wl_keyboard_enter(void *data, wl_keyboard *wl_keyboard, uint32_t serial, wl_surface *surface, wl_array *keys);
    static void wl_keyboard_key(void *data, wl_keyboard *wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
    static void wl_keyboard_keymap(void *data, wl_keyboard *wl_keyboard, uint32_t format, int32_t fd, uint32_t size); // NOLINT(*-identifier-length)
    static void wl_keyboard_leave(void *data, wl_keyboard *wl_keyboard, uint32_t serial, wl_surface *surface);
    static void wl_keyboard_modifiers(void *data, wl_keyboard *wl_keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);
    static void wl_keyboard_repeat_info(void *data, wl_keyboard *wl_keyboard, int32_t rate, int32_t delay);
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
    static void wl_surface_handle_done(void* data, wl_callback* wl_callback, uint32_t time);
    static void xdg_surface_handle_configure(void* data, xdg_surface* xdg_surface, uint32_t serial);
    static void xdg_toplevel_handle_close(void *data, xdg_toplevel *xdg_toplevel);
    static void xdg_toplevel_handle_configure(void* data, xdg_toplevel* xdg_toplevel, int32_t width, int32_t height, wl_array* states);
    static void xdg_toplevel_handle_configure_bounds(void* data, xdg_toplevel* xdg_toplevel, int32_t width, int32_t height);
    static void xdg_toplevel_handle_wm_capabilities(void* data, xdg_toplevel* xdg_toplevel, wl_array* capabilities);
    static void xdg_wm_base_handle_ping(void* data, xdg_wm_base* xdg_wm_base, uint32_t serial);
    // clang-format on

    static const wl_callback_listener&  m_wl_surface_frame_listener;
    static const wl_keyboard_listener&  m_wl_keyboard_listener;
    static const wl_pointer_listener&   m_wl_pointer_listener;
    static const wl_registry_listener&  m_wl_registry_listener;
    static const wl_seat_listener&      m_wl_seat_listener;
    static const xdg_surface_listener&  m_xdg_surface_listener;
    static const xdg_toplevel_listener& m_xdg_toplevel_listener;
    static const xdg_wm_base_listener&  m_xdg_wm_base_listener;
    Vec2<size_t>                        m_size;

public:
    explicit WaylandImpl(WaylandWindow* base);
    ~WaylandImpl();
    WaylandImpl(const WaylandImpl&)            = delete;
    WaylandImpl& operator=(const WaylandImpl&) = delete;
    WaylandImpl(WaylandImpl&&)                 = default;
    WaylandImpl& operator=(WaylandImpl&&)      = default;

    void new_buffer(core::Vec2<size_t> size);
    void render_frame();
    void set_style(WindowStyle style);
};

} // namespace detail

class WaylandWindow final: public Window {
public:
    explicit WaylandWindow(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    ~WaylandWindow() final;
    WaylandWindow(WaylandWindow&&)                 = default;
    WaylandWindow& operator=(WaylandWindow&&)      = default;
    WaylandWindow(const WaylandWindow&)            = delete;
    WaylandWindow& operator=(const WaylandWindow&) = delete;

    void set_style(WindowStyle style);
    void render_frame() final;

private:
    friend class detail::WaylandImpl;
    detail::WaylandImpl m_impl;
};

} // namespace core::window
