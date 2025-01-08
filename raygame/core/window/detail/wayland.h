#pragma once
#include "raygame/core/window/window.h"
#include <chrono>
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>
#include <xkbcommon/xkbcommon.h>

namespace core::window::detail {
class WaylandWindowImpl final: public WindowImpl {
public:
    explicit WaylandWindowImpl(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    WaylandWindowImpl(const WaylandWindowImpl&)           = delete;
    WaylandWindowImpl operator=(const WaylandWindowImpl&) = delete;
    WaylandWindowImpl(WaylandWindowImpl&&)                = default;
    WaylandWindowImpl& operator=(WaylandWindowImpl&&)     = default;
    ~WaylandWindowImpl() final;

    void draw(const drawing::Image& image) final;

    void restyle(WindowStyle style) final;
    void restyle();

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;

private:
    using clock_t     = std::chrono::high_resolution_clock;
    using timepoint_t = std::chrono::time_point<clock_t>;
    timepoint_t m_frame_beg;
    timepoint_t m_frame_end;

    bool m_should_close{false};

    void new_buffer();
    void set_style(WindowStyle style);

    Pixel* data() { return m_pixel_buffer; }

    // NOLINTNEXTLINE(*-pointer-arithmetic)
    Pixel* data_row(size_t col) { return &m_pixel_buffer[col * width()]; }

    void draw_line(std::span<const Pixel> line, Vec2<size_t> pos);

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
        keyboard_state()
            : m_xkb_context(xkb_context_new(XKB_CONTEXT_NO_FLAGS)) {}

        keyboard_state(const keyboard_state&)            = default;
        keyboard_state(keyboard_state&&)                 = default;
        keyboard_state& operator=(const keyboard_state&) = default;
        keyboard_state& operator=(keyboard_state&&)      = default;

        ~keyboard_state() {
            xkb_context_unref(m_xkb_context);
            m_xkb_context = nullptr;
        }

        //NOLINTBEGIN(*-non-private-member-*)
        xkb_state*   m_xkb_state   = nullptr;
        xkb_keymap*  m_xkb_keymap  = nullptr;
        xkb_context* m_xkb_context = nullptr;
        //NOLINTEND(*-non-private-member-*)
    };

    bool           m_configured = false;
    pointer_event  m_pointer_event{};
    keyboard_state m_keyboard_state;

    int      m_shm_fd = -1;
    uint32_t m_wl_shm_format;
    Pixel*   m_pixel_buffer = nullptr;

    wl_buffer*     m_wl_buffer     = nullptr;
    wl_callback*   m_wl_callback   = nullptr;
    wl_compositor* m_wl_compositor = nullptr;
    wl_display*    m_wl_display    = nullptr;
    wl_keyboard*   m_wl_keyboard   = nullptr;
    wl_pointer*    m_wl_pointer    = nullptr;
    wl_registry*   m_wl_registry   = nullptr;
    wl_seat*       m_wl_seat       = nullptr;
    wl_shm*        m_wl_shm        = nullptr;
    wl_shm_pool*   m_wl_shm_pool   = nullptr;
    wl_surface*    m_wl_surface    = nullptr;
    xdg_surface*   m_xdg_surface   = nullptr;
    xdg_toplevel*  m_xdg_toplevel  = nullptr;
    xdg_wm_base*   m_xdg_wm_base   = nullptr;

    // clang-format off
    static void wl_keyboard_enter(void *data, wl_keyboard *wl_keyboard, uint32_t serial, wl_surface *surface, wl_array *keys);
    static void wl_keyboard_key(void *data, wl_keyboard *wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
    static void wl_keyboard_keymap(void *data, wl_keyboard *wl_keyboard, uint32_t format, int32_t shm_fd, uint32_t size);
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

    static const wl_callback_listener  m_wl_surface_frame_listener;
    static const wl_keyboard_listener  m_wl_keyboard_listener;
    static const wl_pointer_listener   m_wl_pointer_listener;
    static const wl_registry_listener  m_wl_registry_listener;
    static const wl_seat_listener      m_wl_seat_listener;
    static const xdg_surface_listener  m_xdg_surface_listener;
    static const xdg_toplevel_listener m_xdg_toplevel_listener;
    static const xdg_wm_base_listener  m_xdg_wm_base_listener;
};
} // namespace core::window::detail
