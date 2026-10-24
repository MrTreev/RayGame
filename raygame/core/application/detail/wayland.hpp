#pragma once
#include "raygame/core/application/application.hpp"
#include "raygame/core/application/detail/wayland/wl_include.hpp"

namespace core::detail {

struct Axis {
    bool       m_valid;
    wl_fixed_t m_value;
    int32_t    m_discrete;
};

struct PointerEvent {
    uint32_t   m_event_mask;
    wl_fixed_t m_surface_x;
    wl_fixed_t m_surface_y;
    uint32_t   m_button;
    uint32_t   m_state;
    uint32_t   m_time;
    uint32_t   m_serial;
    Axis       m_axis_vertical;
    Axis       m_axis_horizontal;
    uint32_t   m_axis_source;
};

enum class Key : uint32_t { // NOLINT(performance-enum-size)
    NONE          = 0,
    // Alphanumeric keys
    APOSTROPHE    = 39, // Key: '
    COMMA         = 44, // Key: ,
    MINUS         = 45, // Key: -
    PERIOD        = 46, // Key: .
    SLASH         = 47, // Key: /
    ZERO          = 48, // Key: 0
    ONE           = 49, // Key: 1
    TWO           = 50, // Key: 2
    THREE         = 51, // Key: 3
    FOUR          = 52, // Key: 4
    FIVE          = 53, // Key: 5
    SIX           = 54, // Key: 6
    SEVEN         = 55, // Key: 7
    EIGHT         = 56, // Key: 8
    NINE          = 57, // Key: 9
    SEMICOLON     = 59, // Key: ;
    EQUAL         = 61, // Key: =
    A             = 65, // Key: A | a
    B             = 66, // Key: B | b
    C             = 67, // Key: C | c
    D             = 68, // Key: D | d
    E             = 69, // Key: E | e
    F             = 70, // Key: F | f
    G             = 71, // Key: G | g
    H             = 72, // Key: H | h
    I             = 73, // Key: I | i
    J             = 74, // Key: J | j
    K             = 75, // Key: K | k
    L             = 76, // Key: L | l
    M             = 77, // Key: M | m
    N             = 78, // Key: N | n
    O             = 79, // Key: O | o
    P             = 80, // Key: P | p
    Q             = 81, // Key: Q | q
    R             = 82, // Key: R | r
    S             = 83, // Key: S | s
    T             = 84, // Key: T | t
    U             = 85, // Key: U | u
    V             = 86, // Key: V | v
    W             = 87, // Key: W | w
    X             = 88, // Key: X | x
    Y             = 89, // Key: Y | y
    Z             = 90, // Key: Z | z
    LEFT_BRACKET  = 91, // Key: [
    BACKSLASH     = 92, // Key: '\'
    RIGHT_BRACKET = 93, // Key: ]
    GRAVE         = 96, // Key: `
    // Function keys
    SPACE         = 32,  // Key: Space
    ESCAPE        = 256, // Key: Esc
    ENTER         = 257, // Key: Enter
    TAB           = 258, // Key: Tab
    BACKSPACE     = 259, // Key: Backspace
    INSERT        = 260, // Key: Ins
    DELETE        = 261, // Key: Del
    RIGHT         = 262, // Key: Cursor right
    LEFT          = 263, // Key: Cursor left
    DOWN          = 264, // Key: Cursor down
    UP            = 265, // Key: Cursor up
    PAGE_UP       = 266, // Key: Page up
    PAGE_DOWN     = 267, // Key: Page down
    HOME          = 268, // Key: Home
    END           = 269, // Key: End
    CAPS_LOCK     = 280, // Key: Caps lock
    SCROLL_LOCK   = 281, // Key: Scroll down
    NUM_LOCK      = 282, // Key: Num lock
    PRINT_SCREEN  = 283, // Key: Print screen
    PAUSE         = 284, // Key: Pause
    F1            = 290, // Key: F1
    F2            = 291, // Key: F2
    F3            = 292, // Key: F3
    F4            = 293, // Key: F4
    F5            = 294, // Key: F5
    F6            = 295, // Key: F6
    F7            = 296, // Key: F7
    F8            = 297, // Key: F8
    F9            = 298, // Key: F9
    F10           = 299, // Key: F10
    F11           = 300, // Key: F11
    F12           = 301, // Key: F12
    LEFT_SHIFT    = 340, // Key: Shift left
    LEFT_CONTROL  = 341, // Key: Control left
    LEFT_ALT      = 342, // Key: Alt left
    LEFT_SUPER    = 343, // Key: Super left
    RIGHT_SHIFT   = 344, // Key: Shift right
    RIGHT_CONTROL = 345, // Key: Control right
    RIGHT_ALT     = 346, // Key: Alt right
    RIGHT_SUPER   = 347, // Key: Super right
    KB_MENU       = 348, // Key: KB menu
    // Keypad keys
    KP_0         = 320, // Key: Keypad 0
    KP_1         = 321, // Key: Keypad 1
    KP_2         = 322, // Key: Keypad 2
    KP_3         = 323, // Key: Keypad 3
    KP_4         = 324, // Key: Keypad 4
    KP_5         = 325, // Key: Keypad 5
    KP_6         = 326, // Key: Keypad 6
    KP_7         = 327, // Key: Keypad 7
    KP_8         = 328, // Key: Keypad 8
    KP_9         = 329, // Key: Keypad 9
    KP_DECIMAL   = 330, // Key: Keypad .
    KP_DIVIDE    = 331, // Key: Keypad /
    KP_MULTIPLY  = 332, // Key: Keypad *
    KP_SUBTRACT  = 333, // Key: Keypad -
    KP_ADD       = 334, // Key: Keypad +
    KP_ENTER     = 335, // Key: Keypad Enter
    KP_EQUAL     = 336, // Key: Keypad =
};

enum class KeyState : uint8_t {
    PRESSED,
    RELEASED,
};

enum class MouseButton : uint8_t {
    LEFT    = 0, // Mouse button left
    RIGHT   = 1, // Mouse button right
    MIDDLE  = 2, // Mouse button middle (pressed wheel)
    SIDE    = 3, // Mouse button side (advanced mouse device)
    EXTRA   = 4, // Mouse button extra (advanced mouse device)
    FORWARD = 5, // Mouse button forward (advanced mouse device)
    BACK    = 6, // Mouse button back (advanced mouse device)
};

class KeyboardState {
    static constexpr size_t BUF_SIZE{64};
    static constexpr int    ADD_VAL{8};

    int m_rate{-1};
    int m_delay{-1};

    struct StateDelete {
        void operator()(xkb_state* state) { xkb_state_unref(state); }
    };

    struct KeymapDelete {
        void operator()(xkb_keymap* keymap) { xkb_keymap_unref(keymap); }
    };

    struct ContextDelete {
        void operator()(xkb_context* context) { xkb_context_unref(context); }
    };

    std::unique_ptr<xkb_context, ContextDelete> m_xkb_context{nullptr};
    std::unique_ptr<xkb_keymap, KeymapDelete>   m_xkb_keymap{nullptr};
    std::unique_ptr<xkb_state, StateDelete>     m_xkb_state{nullptr};

public:
    KeyboardState()
        : m_xkb_context(xkb_context_new(XKB_CONTEXT_NO_FLAGS))
        , m_xkb_keymap(
              xkb_keymap_new_from_names(m_xkb_context.get(), nullptr, XKB_KEYMAP_COMPILE_NO_FLAGS)
          )
        , m_xkb_state(xkb_state_new(m_xkb_keymap.get())) {}

    void new_from_string(const char* str);

    void update_mask(
        uint32_t mods_depressed,
        uint32_t mods_latched,
        uint32_t mods_locked,
        uint32_t group
    );

    void event(const uint32_t& key, const uint32_t& state);

    [[nodiscard]]
    const decltype(m_delay)& rate() const [[clang::lifetimebound]] {
        return m_rate;
    }

    [[nodiscard]]
    const decltype(m_delay)& delay() const [[clang::lifetimebound]] {
        return m_delay;
    }

    void set_rate(int rate) {
        condition::pre_condition(rate > 0, "Invalid keyboard repeat-rate");
        m_rate = rate;
    }

    void set_delay(int delay) {
        condition::pre_condition(delay > 0, "Invalid keyboard repeat-delay");
        m_delay = delay;
    }
};

class AppImplWayland final: public AppImpl {
public:
    AppImplWayland(Vec2<size_t> size, std::string title, WindowStyle style);
    ~AppImplWayland() final;
    AppImplWayland(const AppImplWayland&)           = delete;
    AppImplWayland operator=(const AppImplWayland&) = delete;
    AppImplWayland(AppImplWayland&&)                = default;
    AppImplWayland& operator=(AppImplWayland&&)     = default;

    void draw(const drawing::ImageView& image, const Vec2<pos_t>& position) final;
    void restyle(WindowStyle style) final;
    void restyle();
    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;
    [[nodiscard]]
    bool should_close() const final;
    void set_close() final;
    [[nodiscard]]
    bool is_key_down(Key) const;

private:
    using wl_fixed_t = int32_t;

    static constexpr size_t BUFFER_COUNT = 3;

    std::array<wl_buffer*, BUFFER_COUNT> m_buffers{nullptr};
    std::array<bool, BUFFER_COUNT>       m_busy{false};

    std::mdspan<Pixel, std::dextents<size_t, 2>> m_pixbuf;

    void set_current_pixbuf();
    void recreate_buffers();
    void set_style(WindowStyle style);

    bool          m_should_close = false;
    PointerEvent  m_pointer_event{};
    KeyboardState m_keyboard_state;
    int           m_shm_fd         = -1;
    size_t        m_mapped_size    = 0;
    size_t        m_current_buffer = 0;
    Pixel*        m_mapped_base    = nullptr;
    uint32_t      m_wl_shm_format;
    uint32_t      m_wl_shm_name        = 0;
    uint32_t      m_wl_compositor_name = 0;
    uint32_t      m_xdg_wm_base_name   = 0;
    uint32_t      m_wl_seat_name       = 0;

    size_t m_buffer_width  = 0;
    size_t m_buffer_height = 0;

    // These are intentionally ordered for destruction
    wl_display*    m_wl_display    = nullptr;
    wl_registry*   m_wl_registry   = nullptr;
    wl_shm*        m_wl_shm        = nullptr;
    wl_compositor* m_wl_compositor = nullptr;
    xdg_wm_base*   m_xdg_wm_base   = nullptr;
    wl_surface*    m_wl_surface    = nullptr;
    xdg_surface*   m_xdg_surface   = nullptr;
    xdg_toplevel*  m_xdg_toplevel  = nullptr;
    wl_seat*       m_wl_seat       = nullptr;
    wl_keyboard*   m_wl_keyboard   = nullptr;
    wl_pointer*    m_wl_pointer    = nullptr;
    wl_callback*   m_wl_callback   = nullptr;

    static const wl_buffer_listener    m_wl_buffer_listener;
    static const wl_callback_listener  m_wl_surface_frame_listener;
    static const wl_keyboard_listener  m_wl_keyboard_listener;
    static const wl_pointer_listener   m_wl_pointer_listener;
    static const wl_registry_listener  m_wl_registry_listener;
    static const wl_seat_listener      m_wl_seat_listener;
    static const xdg_surface_listener  m_xdg_surface_listener;
    static const xdg_toplevel_listener m_xdg_toplevel_listener;
    static const xdg_wm_base_listener  m_xdg_wm_base_listener;

    // clang-format off
    static void wl_buffer_release(void *data, wl_buffer *buffer);
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
};
} // namespace core::detail
