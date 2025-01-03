#include "raygame/core/window/window.h" // IWYU pragma: keep
#if defined(RAYGAME_GUI_BACKEND_WAYLAND)
#    include "raygame/core/condition.h"
#    include "raygame/core/drawing/colour.h"
#    include "raygame/core/logger.h"
#    include "raygame/core/math/arithmetic.h"
#    include "raygame/core/math/numeric_cast.h"
#    include "raygame/core/math/random.h"
#    include "raygame/core/window/detail/handlers.h"
#    include <algorithm>
#    include <cstring>
#    include <fcntl.h>
#    include <linux/input-event-codes.h>
#    include <sys/mman.h>
#    include <unistd.h>
#    include <utility>
#    include <wayland-client-protocol.h>
#    include <wayland-util.h>
#    include <xdg-shell-client-protocol.h>
#    include <xkbcommon/xkbcommon.h>

namespace {
using core::condition::check_condition;
using core::condition::check_ptr;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;
using core::math::safe_mult;
using Impl = core::window::Window::Impl;

constexpr std::string_view alnum =
    "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

std::string random_string(
    const size_t&      length,
    const std::string& valid_chars = {alnum.data(), alnum.length()}
) {
    std::string  ret;
    const size_t charlen = valid_chars.size() - 1;
    std::generate_n(std::back_inserter(ret), length, [&] {
        return valid_chars[core::math::rand<size_t>(0, charlen)];
    });
    return ret;
}

int create_shm_file() {
    constexpr int N_RETRIES = 100;
    constexpr int RAND_LEN  = 6;
    for (int retries = N_RETRIES; retries > 0; --retries) {
        std::string name("/wl_shm-");
        name.append(random_string(RAND_LEN));
        const int shm_fd =
            shm_open(name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0600);
        if (shm_fd >= 0) {
            shm_unlink(name.c_str());
            return shm_fd;
        }
    }
    post_condition(false, "Failed to create SHM File Descriptor");
    return -1;
}

int allocate_shm_file(size_t size) {
    pre_condition(size > 0, "Cannot allocate file with size 0");
    const int shm_fd = create_shm_file();
    check_condition(shm_fd >= 0, "Failed to create valid SHM File Descriptor");
    const int ret = ftruncate(shm_fd, numeric_cast<__off_t>(size));
    post_condition(ret == 0, "Could not resize SHM memory-mapped file");
    return shm_fd;
}

wl_shm_format get_colour_format() {
    using core::colour::rgba;
    using std::bit_cast;
    constexpr auto RVAL      = 0b00000000;
    constexpr auto GVAL      = 0b11111111;
    constexpr auto BVAL      = 0b00111100;
    constexpr auto AVAL      = 0b11000011;
    constexpr auto RGBA      = 0b00000000'11111111'00111100'11000011;
    constexpr auto BGRA      = 0b00111100'11111111'00000000'11000011;
    constexpr auto ABGR      = 0b11000011'00111100'11111111'00000000;
    constexpr auto ARGB      = 0b11000011'00000000'11111111'00111100;
    constexpr auto colourval = rgba(RVAL, GVAL, BVAL, AVAL);
    switch (bit_cast<uint32_t>(colourval)) {
    case (ARGB): return WL_SHM_FORMAT_ARGB8888;
    case (ABGR): return WL_SHM_FORMAT_ABGR8888;
    case (BGRA): return WL_SHM_FORMAT_BGRA8888;
    case (RGBA): return WL_SHM_FORMAT_RGBA8888;
    default:
        throw std::invalid_argument(std::format(
            "Could not determine colour format:\n"
            "functdef: {:0>32b}\n"
            "RGBA DEF: {:0>32b}\n"
            "RGBA set: {:0>32b}{:0>32b}{:0>32b}{:0>32b}\n"
            "BYTE NO:  00000000111111112222222233333333\n",
            bit_cast<uint32_t>(colourval),
            RGBA,
            colourval.m_alpha,
            colourval.m_blue,
            colourval.m_green,
            colourval.m_red
        ));
    }
}

enum pointer_event_mask : uint32_t { //NOLINT(*-enum-size)
    POINTER_EVENT_ENTER         = 1U << 0U,
    POINTER_EVENT_LEAVE         = 1U << 1U,
    POINTER_EVENT_MOTION        = 1U << 2U,
    POINTER_EVENT_BUTTON        = 1U << 3U,
    POINTER_EVENT_AXIS          = 1U << 4U,
    POINTER_EVENT_AXIS_SOURCE   = 1U << 5U,
    POINTER_EVENT_AXIS_STOP     = 1U << 6U,
    POINTER_EVENT_AXIS_DISCRETE = 1U << 7U,
};

constexpr uint32_t ALL_AXIS_EVENTS =
    (POINTER_EVENT_AXIS | POINTER_EVENT_AXIS_SOURCE | POINTER_EVENT_AXIS_STOP
     | POINTER_EVENT_AXIS_DISCRETE);

constexpr std::string source_string(uint32_t axis_source) {
    switch (axis_source) {
    case WL_POINTER_AXIS_SOURCE_WHEEL:      return " source(wheel) ";
    case WL_POINTER_AXIS_SOURCE_FINGER:     return " source(finger) ";
    case WL_POINTER_AXIS_SOURCE_CONTINUOUS: return " source(continuous) ";
    case WL_POINTER_AXIS_SOURCE_WHEEL_TILT: return " source(wheel tilt) ";
    default:                                return " ";
    }
}
} // namespace

class WaylandPointer {
    friend PointerHandler;
    static const PointerHandler m_pointer_handler;
    wl_pointer*                 m_wl_pointer{nullptr};

    class pointer_event {
    public:
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

    pointer_event m_event{};

public:
    void bind(wl_pointer* pointer) {
        check_ptr(pointer, "cannot bind WaylandPointer to nullptr");
        m_wl_pointer = pointer;
    }

    [[nodiscard]]
    bool exists() const {
        return m_wl_pointer != nullptr;
    }

    void add_listener(Impl* self) {
        check_ptr(m_wl_pointer, "cannot add listener to null wl_pointer");
        wl_pointer_add_listener(m_wl_pointer, &PointerHandler::listener, self);
    }

    void release() {
        if (m_wl_pointer != nullptr) {
            wl_pointer_release(m_wl_pointer);
            m_wl_pointer = nullptr;
        }
    }
};

class WaylandKeyboard {
    static const KeyboardHandler m_keyboard_handler;
    xkb_state*                   m_xkb_state   = nullptr;
    xkb_keymap*                  m_xkb_keymap  = nullptr;
    xkb_context*                 m_xkb_context = nullptr;
    wl_keyboard*                 m_wl_keyboard = nullptr;

public:
    WaylandKeyboard()
        : m_xkb_context(xkb_context_new(XKB_CONTEXT_NO_FLAGS)) {}

    ~WaylandKeyboard() {
        if (m_xkb_context != nullptr) {
            xkb_context_unref(m_xkb_context);
            m_xkb_context = nullptr;
        }
    }

    WaylandKeyboard(const WaylandKeyboard&)            = delete;
    WaylandKeyboard& operator=(const WaylandKeyboard&) = delete;
    WaylandKeyboard(WaylandKeyboard&&)                 = default;
    WaylandKeyboard& operator=(WaylandKeyboard&&)      = default;

    void bind(wl_keyboard* keyboard) {
        check_ptr(keyboard, "cannot bind WaylandKeyboard to nullptr");
        m_wl_keyboard = keyboard;
    }

    [[nodiscard]]
    bool exists() const {
        return m_wl_keyboard != nullptr;
    }

    void add_listener(Impl* self) {
        check_ptr(m_wl_keyboard, "cannot add listener to null wl_keyboard");
        wl_keyboard_add_listener(
            m_wl_keyboard,
            &KeyboardHandler::listener,
            self
        );
    }

    void release() {
        if (m_wl_keyboard != nullptr) {
            wl_keyboard_release(m_wl_keyboard);
            m_wl_keyboard = nullptr;
        }
    }

    void     set(int32_t file_desc, uint32_t size);
    uint32_t keysym(uint32_t key, std::span<char> buf);
    void     update(
            uint32_t mods_depressed,
            uint32_t mods_latched,
            uint32_t mods_locked,
            uint32_t group
        );
};

class WaylandDisplay {
    wl_display* m_wl_display{nullptr};

public:
    explicit WaylandDisplay(const char* name);

    [[nodiscard]]
    wl_display* get() const {
        return m_wl_display;
    }

    [[nodiscard]]
    int roundtrip() {
        return wl_display_roundtrip(m_wl_display);
    }

    [[nodiscard]]
    int dispatch() {
        return wl_display_dispatch(m_wl_display);
    }
};

class WaylandRegistry {
    static const RegistryHandler m_registry_handler;
    wl_registry*                 m_wl_registry{nullptr};

public:
    explicit WaylandRegistry(WaylandDisplay display, Impl* base);

    [[nodiscard]]
    auto* get() const {
        return m_wl_registry;
    }
};

class WaylandBuffer {
    wl_buffer*   m_wl_buffer   = nullptr;
    wl_shm*      m_wl_shm      = nullptr;
    wl_shm_pool* m_wl_shm_pool = nullptr;
    int          m_shm_fd{-1};
    uint32_t     m_wl_shm_format;
    uint8_t*     m_pixel_buffer{nullptr};

public:
    WaylandBuffer()
        : m_wl_shm_format(get_colour_format()) {}

    WaylandBuffer(const WaylandBuffer&)            = delete;
    WaylandBuffer& operator=(const WaylandBuffer&) = delete;
    WaylandBuffer(WaylandBuffer&&)                 = default;
    WaylandBuffer& operator=(WaylandBuffer&&)      = default;

    ~WaylandBuffer() { wl_buffer_destroy(m_wl_buffer); }

    void bind(wl_shm* shm) {
        m_wl_shm = shm;
        check_ptr(m_wl_shm, "shm bind given nullptr");
    }

    void new_buffer(core::Vec2<size_t> size) {
        constexpr size_t COLOUR_CHANNELS{4};
        const auto       buflen{safe_mult<size_t>(size.x, size.y)};
        const auto       bufsize{safe_mult<size_t>(buflen, COLOUR_CHANNELS)};
        if (m_wl_shm_pool != nullptr) {
            wl_shm_pool_destroy(m_wl_shm_pool);
        }
        if (m_shm_fd >= 0) {
            close(m_shm_fd);
            m_shm_fd = -1;
        }
        m_shm_fd = allocate_shm_file(bufsize);
        check_condition(m_shm_fd >= 0, "creation of shm buffer file failed");
        m_pixel_buffer = static_cast<uint8_t*>(mmap(
            nullptr,
            bufsize,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            m_shm_fd,
            0
        ));
        if (m_pixel_buffer == MAP_FAILED) {
            close(m_shm_fd);
            check_condition(false, "Could not setup shm data");
        }
        m_wl_shm_pool = wl_shm_create_pool(
            m_wl_shm,
            m_shm_fd,
            numeric_cast<int32_t>(bufsize)
        );
        m_wl_buffer = wl_shm_pool_create_buffer(
            m_wl_shm_pool,
            0,
            numeric_cast<int32_t>(size.x),
            numeric_cast<int32_t>(size.y),
            safe_mult<int32_t>(size.x, COLOUR_CHANNELS),
            m_wl_shm_format
        );
        check_ptr(m_wl_buffer, "Failed to create buffer");
    }

    wl_buffer* data() { return m_wl_buffer; }
};

class WaylandSurface {
    static const SurfaceHandler     m_surface_handler;
    static const XdgSurfaceHandler  m_xdg_surface_handler;
    static const XdgToplevelHandler m_xdg_toplevel_handler;
    wl_surface*                     m_wl_surface   = nullptr;
    xdg_surface*                    m_xdg_surface  = nullptr;
    xdg_toplevel*                   m_xdg_toplevel = nullptr;

public:
    WaylandSurface(wl_compositor* compositor, xdg_wm_base* wm_base, Impl* base);
    ~WaylandSurface();
    WaylandSurface(const WaylandSurface&)            = delete;
    WaylandSurface& operator=(const WaylandSurface&) = delete;
    WaylandSurface(WaylandSurface&&)                 = default;
    WaylandSurface& operator=(WaylandSurface&&)      = default;

    void add_listeners(Impl* base);
    void commit();
    void set_title(const std::string& title);
    void attach(WaylandBuffer& buffer, int32_t xpos, int32_t ypos);

    void damage(core::Rect<int32_t> rect) {
        wl_surface_damage_buffer(
            m_wl_surface,
            rect.pos().x,
            rect.pos().y,
            rect.pos().x + rect.width(),
            rect.pos().y + rect.height()
        );
    }

    void set_fullscreen() {
        xdg_toplevel_set_fullscreen(m_xdg_toplevel, nullptr);
    }

    void set_windowed_full() {
        xdg_toplevel_unset_fullscreen(m_xdg_toplevel);
        xdg_toplevel_set_maximized(m_xdg_toplevel);
    }

    void set_window() {
        xdg_toplevel_unset_fullscreen(m_xdg_toplevel);
        xdg_toplevel_unset_maximized(m_xdg_toplevel);
    }

    [[nodiscard]]
    wl_surface* wl_surface() const {
        return m_wl_surface;
    }
};

class WaylandCallback {
    wl_callback* m_wl_callback = nullptr;

public:
    explicit WaylandCallback(const WaylandSurface& surface, Impl* base)
        : m_wl_callback(wl_surface_frame(surface.wl_surface())) {
        check_ptr(m_wl_callback, "Failed to create callback");
        wl_callback_add_listener(
            m_wl_callback,
            &SurfaceHandler::listener,
            base
        );
    }
};

class core::window::Window::Impl {
    using wl_fixed_t = int32_t;

    Vec2<size_t> m_size{DEFAULT_WINDOW_SIZE};
    std::string  m_title{DEFAULT_WINDOW_TITLE};
    WindowStyle  m_style{DEFAULT_WINDOW_STYLE};
    bool         m_should_close{false};

    bool     m_configured = false;
    uint32_t m_last_frame = 0;

public:
    explicit Impl(
        core::Vec2<size_t> size,
        std::string        title,
        WindowStyle        style
    );
    ~Impl();
    Impl(const Impl&)            = delete;
    Impl& operator=(const Impl&) = delete;
    Impl(Impl&&)                 = default;
    Impl& operator=(Impl&&)      = default;

    void new_buffer();
    void render_frame();
    void set_style(WindowStyle style);

    void set_close() { m_should_close = true; }

    [[nodiscard]]
    const size_t& buf_width() const {
        return m_size.x;
    }

    [[nodiscard]]
    const size_t& buf_height() const {
        return m_size.y;
    }

    [[nodiscard]]
    bool should_close() const {
        return m_should_close;
    }
};

uint32_t WaylandKeyboard::keysym(uint32_t key, std::span<char> buf) {
    constexpr int      ADD_VAL{8};
    const xkb_keysym_t sym =
        xkb_state_key_get_one_sym(m_xkb_state, key + ADD_VAL);
    xkb_keysym_get_name(sym, buf.data(), buf.size());
    return sym;
}

void WaylandKeyboard::set(int32_t file_desc, uint32_t size) {
    char* map_shm = static_cast<char*>(
        mmap(nullptr, size, PROT_READ, MAP_SHARED, file_desc, 0)
    );
    core::condition::check_condition(
        map_shm != MAP_FAILED,
        "Failed keyboard shm map"
    );
    xkb_keymap* xkb_keymap = xkb_keymap_new_from_string(
        m_xkb_context,
        map_shm,
        XKB_KEYMAP_FORMAT_TEXT_V1,
        XKB_KEYMAP_COMPILE_NO_FLAGS
    );
    core::condition::check_ptr(xkb_keymap, "Failed to create new xkb_keymap");
    munmap(map_shm, size);
    close(file_desc);
    xkb_state* xkb_state = xkb_state_new(xkb_keymap);
    core::condition::check_ptr(xkb_state, "Failed to create new xkb_state");
    xkb_keymap_unref(m_xkb_keymap);
    xkb_state_unref(m_xkb_state);
    m_xkb_keymap = xkb_keymap;
    m_xkb_state  = xkb_state;
}

WaylandRegistry::WaylandRegistry(WaylandDisplay display, Impl* base)
    : m_wl_registry(wl_display_get_registry(display.get())) {
    check_ptr(m_wl_registry, "Registry setup failed");
    wl_registry_add_listener(m_wl_registry, &RegistryHandler::listener, this);
    check_condition(display.roundtrip() != 0, "Display roundtrip failed");
    while ((base->m_display.dispatch() != -1) && (!base->m_configured)) {
        core::log::error("Wayland display not configured");
    }
    core::log::trace("Display Dispatched");
}

void WaylandSurface::attach(
    WaylandBuffer& buffer,
    int32_t        xpos = 0,
    int32_t        ypos = 0
) {
    wl_surface_attach(m_wl_surface, buffer.data(), xpos, ypos);
    core::log::trace("Surface Attached");
}

WaylandSurface::WaylandSurface(
    wl_compositor* compositor,
    xdg_wm_base*   wm_base,
    Impl*          base
)
    : m_wl_surface(wl_compositor_create_surface(compositor))
    , m_xdg_surface(xdg_wm_base_get_xdg_surface(wm_base, m_wl_surface))
    , m_xdg_toplevel(xdg_surface_get_toplevel(m_xdg_surface)) {
    check_ptr(m_wl_surface, "wl_surface setup failed");
    check_ptr(m_xdg_surface, "xdg_surface setup failed");
    check_ptr(m_xdg_toplevel, "xdg_toplevel setup failed");
    check_ptr(compositor, "compositor global setup failed");
    check_ptr(wm_base, "xdg_wm_base global setup failed");
    add_listeners(base);
    commit();
}

WaylandSurface::~WaylandSurface() {
    wl_surface_destroy(m_wl_surface);
    xdg_surface_destroy(m_xdg_surface);
    xdg_toplevel_destroy(m_xdg_toplevel);
}

void WaylandSurface::set_title(const std::string& title) {
    xdg_toplevel_set_title(m_xdg_toplevel, title.c_str());
}

void WaylandSurface::commit() {
    wl_surface_commit(m_wl_surface);
    core::log::trace("Surface Committed");
}

void WaylandSurface::add_listeners(Impl* base) {
    xdg_toplevel_add_listener(
        m_xdg_toplevel,
        &XdgToplevelHandler::listener,
        base
    );
    xdg_surface_add_listener(m_xdg_surface, &XdgSurfaceHandler::listener, base);
}

void WaylandKeyboard::update(
    uint32_t mods_depressed,
    uint32_t mods_latched,
    uint32_t mods_locked,
    uint32_t group
) {
    xkb_state_update_mask(
        m_xkb_state,
        mods_depressed,
        mods_latched,
        mods_locked,
        0,
        0,
        group
    );
}

WaylandDisplay::WaylandDisplay(const char* name)
    : m_wl_display(wl_display_connect(name)) {
    check_ptr(m_wl_display, "Display setup failed");
}

core::window::Window::Impl::Impl(
    core::Vec2<size_t> size,
    std::string        title,
    WindowStyle        style
)
    : m_size(size)
    , m_title(std::move(title))
    , m_style(style)
    , m_display(nullptr)
    , m_registry(m_display, this)
    , m_surface(m_wl_compositor, m_xdg_wm_base, this)
    , m_callback(m_surface, this) {
    m_surface.set_title(m_title);
    new_buffer();
    set_style(m_style);
    m_surface.commit();
    core::log::trace("Return from Constructor");
}

core::window::Window::Impl::~Impl() = default;

void core::window::Window::Impl::new_buffer() {
    m_buffer.new_buffer(m_size);
}

void core::window::Window::Impl::render_frame() {
    check_condition(m_display.dispatch(), "Failed to dispatch frame");
}

void core::window::Window::Impl::set_style(core::window::WindowStyle style) {
    switch (style) {
    case WindowStyle::Windowed:           m_surface.set_window(); return;
    case WindowStyle::WindowedFullscreen: m_surface.set_windowed_full(); return;
    case WindowStyle::Fullscreen:         m_surface.set_fullscreen(); return;
    }
}

void core::window::Window::draw(const drawing::Image& image) {
    std::ignore = image;
}

void core::window::Window::render_frame() {
    m_impl->render_frame();
}

bool core::window::Window::next_frame() {
    if (!should_close()) {
        render_frame();
    }
    return !should_close();
}

bool core::window::Window::should_close() const {
    return m_impl->should_close();
}

const core::size_t& core::window::Window::buf_width() const {
    return m_impl->buf_width();
}

const core::size_t& core::window::Window::buf_height() const {
    return m_impl->buf_height();
}

void core::window::Window::set_style(WindowStyle style) {
    m_impl->set_style(style);
}

core::window::Window::Window(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : m_impl(new Impl(size, std::move(title), style)) {}

core::window::Window::~Window() {
    delete m_impl;
}

#endif
