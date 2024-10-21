#include "core/window/detail/wayland.h" // IWYU pragma: keep
#include "core/base/condition.h"
#include "core/base/logger.h"
#include "core/drawing/colour.h"
#include "core/math/arithmetic.h"
#include "core/math/math.h"
#include "core/math/random.h"
#include "core/window/wayland.h"
#include <cstring>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include <xdg-shell-client-protocol.h>
#include <xkbcommon/xkbcommon.h>

using core::condition::check_condition;
using core::condition::check_ptr;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;
using core::math::safe_mult;

namespace {

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

constexpr uint32_t ALL_AXIS_EVENTS =
    (POINTER_EVENT_AXIS | POINTER_EVENT_AXIS_SOURCE | POINTER_EVENT_AXIS_STOP
     | POINTER_EVENT_AXIS_DISCRETE);

constexpr std::string_view alnum =
    "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

std::string random_string(
    const size_t&      length,
    const std::string& valid_chars = alnum.data()
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
    constexpr auto colourval =
        rgba(0b00000000, 0b11111111, 0b00111100, 0b11000011);
    switch (bit_cast<uint32_t>(colourval)) {
    case (0b11000011'00000000'11111111'00111100):
        return WL_SHM_FORMAT_ARGB8888;
    case (0b11000011'00111100'11111111'00000000):
        return WL_SHM_FORMAT_ABGR8888;
    case (0b00111100'11111111'00000000'11000011):
        return WL_SHM_FORMAT_BGRA8888;
    case (0b00000000'11111111'00111100'11000011):
        return WL_SHM_FORMAT_RGBA8888;
    default:
        throw std::invalid_argument(std::format(
            "Could not determine colour format:\n"
            "functdef: {:0>32b}\n"
            "RGBA DEF: {:0>32b}\n"
            "RGBA set: {:0>32b}{:0>32b}{:0>32b}{:0>32b}\n"
            "BYTE NO:  00000000111111112222222233333333\n",
            bit_cast<uint32_t>(colourval),
            (0b00000000'11111111'00111100'11000011),
            colourval.m_alpha,
            colourval.m_blue,
            colourval.m_green,
            colourval.m_red
        ));
    }
}

constexpr size_t COLOUR_CHANNELS = 4;

} // namespace

core::window::detail::keyboard_state::keyboard_state() {
    m_xkb_context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
}

core::window::detail::keyboard_state::~keyboard_state() {
    xkb_context_unref(m_xkb_context);
    m_xkb_context = nullptr;
}

core::window::detail::WaylandImpl::WaylandImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : m_size(size) {
    m_wl_display = wl_display_connect(nullptr);
    check_ptr(m_wl_display, "Display setup failed");
    m_wl_registry = wl_display_get_registry(m_wl_display);
    check_ptr(m_wl_registry, "Registry setup failed");
    wl_registry_add_listener(m_wl_registry, &m_wl_registry_listener, this);
    check_condition(
        wl_display_roundtrip(m_wl_display) != 0,
        "Display roundtrip failed"
    );
    check_ptr(m_wl_shm, "shm global setup failed");
    check_ptr(m_wl_compositor, "compositor global setup failed");
    check_ptr(m_xdg_wm_base, "xdg_wm_base global setup failed");
    m_wl_surface = wl_compositor_create_surface(m_wl_compositor);
    check_ptr(m_wl_surface, "wl_surface setup failed");
    m_xdg_surface = xdg_wm_base_get_xdg_surface(m_xdg_wm_base, m_wl_surface);
    check_ptr(m_xdg_surface, "xdg_surface setup failed");
    m_xdg_toplevel = xdg_surface_get_toplevel(m_xdg_surface);
    check_ptr(m_xdg_toplevel, "xdg_toplevel setup failed");
    xdg_surface_add_listener(m_xdg_surface, &m_xdg_surface_listener, this);
    wl_surface_commit(m_wl_surface);
    core::log::trace("Surface Committed");
    while ((wl_display_dispatch(m_wl_display) != -1) && (!m_configured)) {
        core::log::error("Wayland display not configured");
    }
    core::log::debug("Display Dispatched");
    xdg_toplevel_set_title(m_xdg_toplevel, title.c_str());
    new_buffer(m_size);
    set_style(style);
    wl_surface_attach(m_wl_surface, m_wl_buffer, 0, 0);
    wl_surface_commit(m_wl_surface);
    m_wl_callback = wl_surface_frame(m_wl_surface);
    check_ptr(m_wl_callback, "Failed to create callback");
    wl_callback_add_listener(m_wl_callback, &m_wl_surface_frame_listener, this);
}

core::window::detail::WaylandImpl::~WaylandImpl() {
    wl_buffer_destroy(m_wl_buffer);
    wl_surface_destroy(m_wl_surface);
    xdg_surface_destroy(m_xdg_surface);
    xdg_toplevel_destroy(m_xdg_toplevel);
}

void core::window::detail::WaylandImpl::new_buffer(core::Vec2<size_t> size) {
    const size_t buflen  = safe_mult<size_t>(size.x, size.y);
    const size_t bufsize = safe_mult<size_t>(buflen, COLOUR_CHANNELS);
    const int    shm_fd  = allocate_shm_file(bufsize);
    check_condition(shm_fd >= 0, "creation of shm buffer file failed");
    auto shm_data =
        mmap(nullptr, bufsize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_data == MAP_FAILED) {
        close(shm_fd);
        check_condition(false, "Could not setup shm data");
    }
    wl_shm_pool* pool =
        wl_shm_create_pool(m_wl_shm, shm_fd, numeric_cast<int32_t>(bufsize));
    m_wl_buffer = wl_shm_pool_create_buffer(
        pool,
        0,
        numeric_cast<int32_t>(size.x),
        numeric_cast<int32_t>(size.y),
        safe_mult<int32_t>(size.x, COLOUR_CHANNELS),
        get_colour_format()
    );
    wl_shm_pool_destroy(pool);
    close(shm_fd);
    check_ptr(m_wl_buffer, "Failed to create buffer");
}

bool core::window::detail::WaylandImpl::next_frame() {
    if (!should_close()) {
        wl_display_dispatch(m_wl_display);
    }
    return !should_close();
}

void core::window::detail::WaylandImpl::set_style(
    core::window::WindowStyle style
) {
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

void core::window::detail::WaylandImpl::wl_keyboard_enter(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface,
    [[maybe_unused]] wl_array*    keys
) {
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    for (size_t i = 0; i > keys->size; ++i) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
        char key = static_cast<char*>(keys->data)[i];
#pragma clang diagnostic pop
        std::array<char, 128> buf;
        xkb_keysym_t          sym = xkb_state_key_get_one_sym(
            this_impl->m_keyboard_state.m_xkb_state,
            static_cast<xkb_keycode_t>(key + 8)
        );
        xkb_keysym_get_name(sym, buf.data(), buf.size());
        log::trace(std::format("sym: {} ({})", buf.data(), sym));
    }
}

void core::window::detail::WaylandImpl::wl_keyboard_key(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     time,
    [[maybe_unused]] uint32_t     key,
    [[maybe_unused]] uint32_t     state
) {
    WaylandImpl*          this_impl = static_cast<WaylandImpl*>(data);
    std::array<char, 128> buf;
    uint32_t              keycode = key + 8;
    xkb_keysym_t          sym     = xkb_state_key_get_one_sym(
        this_impl->m_keyboard_state.m_xkb_state,
        keycode
    );
    xkb_keysym_get_name(sym, buf.data(), sizeof(buf));
    log::trace(std::format(
        "key {}: sym: {} ({}), ",
        (state == WL_KEYBOARD_KEY_STATE_PRESSED) ? "press" : "release",
        buf.data(),
        sym
    ));
}

void core::window::detail::WaylandImpl::wl_keyboard_keymap(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     format,
    [[maybe_unused]] int32_t      fd,
    [[maybe_unused]] uint32_t     size
) {
    core::condition::pre_condition(
        format == WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1,
        "Invalid WL_KEYBOARD_KEYMAP_FORMAT"
    );
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    char*        map_shm =
        static_cast<char*>(mmap(nullptr, size, PROT_READ, MAP_SHARED, fd, 0));
    core::condition::check_condition(
        map_shm != MAP_FAILED,
        "Failed keyboard shm map"
    );
    xkb_keymap* xkb_keymap = xkb_keymap_new_from_string(
        this_impl->m_keyboard_state.m_xkb_context,
        map_shm,
        XKB_KEYMAP_FORMAT_TEXT_V1,
        XKB_KEYMAP_COMPILE_NO_FLAGS
    );
    core::condition::check_ptr(xkb_keymap, "Failed to create new xkb_keymap");
    munmap(map_shm, size);
    close(fd);
    xkb_state* xkb_state = xkb_state_new(xkb_keymap);
    core::condition::check_ptr(xkb_state, "Failed to create new xkb_state");
    xkb_keymap_unref(this_impl->m_keyboard_state.m_xkb_keymap);
    xkb_state_unref(this_impl->m_keyboard_state.m_xkb_state);
    this_impl->m_keyboard_state.m_xkb_keymap = xkb_keymap;
    this_impl->m_keyboard_state.m_xkb_state  = xkb_state;
}

void core::window::detail::WaylandImpl::wl_keyboard_leave(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface
) {
    core::log::trace("Keyboard Leave");
}

void core::window::detail::WaylandImpl::wl_keyboard_modifiers(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     mods_depressed,
    [[maybe_unused]] uint32_t     mods_latched,
    [[maybe_unused]] uint32_t     mods_locked,
    [[maybe_unused]] uint32_t     group
) {
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    xkb_state_update_mask(
        this_impl->m_keyboard_state.m_xkb_state,
        mods_depressed,
        mods_latched,
        mods_locked,
        0,
        0,
        group
    );
}

void core::window::detail::WaylandImpl::wl_keyboard_repeat_info(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] int32_t      rate,
    [[maybe_unused]] int32_t      delay
) {}

void core::window::detail::WaylandImpl::wl_pointer_handle_axis(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    time,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] wl_fixed_t  value
) {
    WaylandImpl* this_impl                 = static_cast<WaylandImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_AXIS;
    this_impl->m_pointer_event.time        = time;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        this_impl->m_pointer_event.axis_vertical.valid = true;
        this_impl->m_pointer_event.axis_vertical.value = value;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        this_impl->m_pointer_event.axis_horizontal.valid = true;
        this_impl->m_pointer_event.axis_horizontal.value = value;
    }
    RAYGAME_ELSE_UNKNOWN("axis");
}

void core::window::detail::WaylandImpl::wl_pointer_handle_axis_discrete(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] int32_t     discrete
) {
    [[maybe_unused]]
    WaylandImpl* this_impl                 = static_cast<WaylandImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_AXIS_DISCRETE;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        this_impl->m_pointer_event.axis_vertical.valid    = true;
        this_impl->m_pointer_event.axis_vertical.discrete = discrete;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        this_impl->m_pointer_event.axis_horizontal.valid    = true;
        this_impl->m_pointer_event.axis_horizontal.discrete = discrete;
    }
    RAYGAME_ELSE_UNKNOWN("axis");
}

void core::window::detail::WaylandImpl::
    wl_pointer_handle_axis_relative_direction(
        [[maybe_unused]] void*       data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        [[maybe_unused]] uint32_t    axis,
        [[maybe_unused]] uint32_t    direction
    ) {
    [[maybe_unused]]
    const WaylandImpl* const this_impl = static_cast<WaylandImpl*>(data);
}

void core::window::detail::WaylandImpl::wl_pointer_handle_axis_source(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis_source
) {
    [[maybe_unused]]
    WaylandImpl* this_impl                  = static_cast<WaylandImpl*>(data);
    this_impl->m_pointer_event.event_mask  |= POINTER_EVENT_AXIS_SOURCE;
    this_impl->m_pointer_event.axis_source  = axis_source;
}

void core::window::detail::WaylandImpl::wl_pointer_handle_axis_stop(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis
) {
    [[maybe_unused]]
    WaylandImpl* this_impl                 = static_cast<WaylandImpl*>(data);
    this_impl->m_pointer_event.time        = time;
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_AXIS_STOP;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        this_impl->m_pointer_event.axis_vertical.valid = true;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        this_impl->m_pointer_event.axis_horizontal.valid = true;
    }
    RAYGAME_ELSE_UNKNOWN("axis");
}

void core::window::detail::WaylandImpl::wl_pointer_handle_axis_value120(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] int32_t     value120
) {
    [[maybe_unused]]
    const WaylandImpl* const this_impl = static_cast<WaylandImpl*>(data);
}

void core::window::detail::WaylandImpl::wl_pointer_handle_button(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* pointer,
    [[maybe_unused]] uint32_t    serial,
    [[maybe_unused]] uint32_t    time,
    [[maybe_unused]] uint32_t    button,
    [[maybe_unused]] uint32_t    state
) {
    WaylandImpl* this_impl                 = static_cast<WaylandImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_BUTTON;
    this_impl->m_pointer_event.time        = time;
    this_impl->m_pointer_event.serial      = serial;
    this_impl->m_pointer_event.button      = button;
    this_impl->m_pointer_event.state       = state;
}

void core::window::detail::WaylandImpl::wl_pointer_handle_enter(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    serial,
    [[maybe_unused]] wl_surface* surface,
    [[maybe_unused]] wl_fixed_t  surface_x,
    [[maybe_unused]] wl_fixed_t  surface_y
) {
    WaylandImpl* this_impl                 = static_cast<WaylandImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_ENTER;
    this_impl->m_pointer_event.serial      = serial;
    this_impl->m_pointer_event.surface_x   = surface_x;
    this_impl->m_pointer_event.surface_y   = surface_y;
}

void core::window::detail::WaylandImpl::wl_pointer_handle_frame(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer
) {
    WaylandImpl*   this_impl = static_cast<WaylandImpl*>(data);
    pointer_event& event     = this_impl->m_pointer_event;
    if (event.event_mask & POINTER_EVENT_ENTER) {
        core::log::trace(std::format(
            "Pointer Entry ({}, {})",
            wl_fixed_to_double(event.surface_x),
            wl_fixed_to_double(event.surface_y)
        ));
    }
    if (event.event_mask & POINTER_EVENT_LEAVE) {
        core::log::trace("Pointer Leave");
    }
    if (event.event_mask & POINTER_EVENT_MOTION) {
        core::log::trace(std::format(
            "Pointer Motion ({}, {})",
            wl_fixed_to_double(event.surface_x),
            wl_fixed_to_double(event.surface_y)
        ));
    }
    if (event.event_mask & POINTER_EVENT_BUTTON) {
        if (event.state & WL_POINTER_BUTTON_STATE_PRESSED) {
            core::log::trace(std::format("Button {} pressed", event.button));
        } else if (event.state & WL_POINTER_BUTTON_STATE_RELEASED) {
            core::log::trace(std::format("Button {} released", event.button));
        }
        RAYGAME_ELSE_UNKNOWN("button state");
    }
    if (event.event_mask & ALL_AXIS_EVENTS) {
        const auto handle_axis = [event](const axis_t& axis) {
            std::string ret_str = "Axis event:";
            if (event.event_mask & POINTER_EVENT_AXIS) {
                ret_str +=
                    std::format(" axis({}) ", wl_fixed_to_double(axis.value));
            }
            if (event.event_mask & POINTER_EVENT_AXIS_DISCRETE) {
                ret_str += std::format(" discrete({}) ", axis.discrete);
            }
            if (event.event_mask & POINTER_EVENT_AXIS_SOURCE) {
                if (event.axis_source == WL_POINTER_AXIS_SOURCE_WHEEL) {
                    ret_str += std::format(" source(wheel) ");
                } else if (event.axis_source == WL_POINTER_AXIS_SOURCE_FINGER) {
                    ret_str += std::format(" source(finger) ");
                } else if (event.axis_source
                           == WL_POINTER_AXIS_SOURCE_CONTINUOUS) {
                    ret_str += std::format(" source(continuous) ");
                } else if (event.axis_source
                           == WL_POINTER_AXIS_SOURCE_WHEEL_TILT) {
                    ret_str += std::format(" source(wheel tilt) ");
                }
            }
            return ret_str;
        };
        if (event.axis_vertical.valid) {
            core::log::trace(handle_axis(event.axis_horizontal));
        }
        if (event.axis_horizontal.valid) {
            core::log::trace(handle_axis(event.axis_vertical));
        }
    }
    std::memset(&event, 0, sizeof(event));
}

void core::window::detail::WaylandImpl::wl_pointer_handle_leave(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    serial,
    [[maybe_unused]] wl_surface* surface
) {
    WaylandImpl* this_impl                 = static_cast<WaylandImpl*>(data);
    this_impl->m_pointer_event.serial      = serial;
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_LEAVE;
}

void core::window::detail::WaylandImpl::wl_pointer_handle_motion(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    time,
    [[maybe_unused]] wl_fixed_t  surface_x,
    [[maybe_unused]] wl_fixed_t  surface_y
) {
    WaylandImpl* this_impl                 = static_cast<WaylandImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_MOTION;
    this_impl->m_pointer_event.time        = time;
    this_impl->m_pointer_event.surface_x   = surface_x;
    this_impl->m_pointer_event.surface_y   = surface_y;
}

void core::window::detail::WaylandImpl::wl_registry_handle_global(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_registry* registry,
    [[maybe_unused]] uint32_t     name,
    [[maybe_unused]] const char*  interface,
    [[maybe_unused]] uint32_t     version
) {
    WaylandImpl*      this_impl = static_cast<WaylandImpl*>(data);
    const std::string interface_str{interface};
    if (interface_str == wl_shm_interface.name) {
        core::log::trace(std::format("Handled Global: {}", interface));
        this_impl->m_wl_shm = static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, version)
        );
    } else if (interface_str == wl_compositor_interface.name) {
        core::log::trace(std::format("Handled Global: {}", interface));
        this_impl->m_wl_compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, version)
        );
    } else if (interface_str == xdg_wm_base_interface.name) {
        core::log::trace(std::format("Handled Global: {}", interface));
        this_impl->m_xdg_wm_base = static_cast<xdg_wm_base*>(
            wl_registry_bind(registry, name, &xdg_wm_base_interface, version)
        );
        xdg_wm_base_add_listener(
            this_impl->m_xdg_wm_base,
            &m_xdg_wm_base_listener,
            this_impl
        );
    } else if (interface_str == wl_seat_interface.name) {
        core::log::trace(std::format("Handled Global: {}", interface));
        this_impl->m_wl_seat = static_cast<wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface, version)
        );
        wl_seat_add_listener(
            this_impl->m_wl_seat,
            &m_wl_seat_listener,
            this_impl
        );
    } else {
        core::log::trace(std::format("Unhandled Global: {}", interface));
    }
}

void core::window::detail::WaylandImpl::wl_registry_handle_global_remove(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_registry* registry,
    [[maybe_unused]] uint32_t     name
) {
    [[maybe_unused]]
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    wl_registry_destroy(registry);
    core::log::trace(std::format("removed registry: {}", name));
}

void core::window::detail::WaylandImpl::wl_seat_handle_capabilities(
    [[maybe_unused]] void*    data,
    [[maybe_unused]] wl_seat* seat,
    [[maybe_unused]] uint32_t capabilities
) {
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    bool have_pointer      = (capabilities != 0U) && WL_SEAT_CAPABILITY_POINTER;
    bool have_keyboard     = capabilities & WL_SEAT_CAPABILITY_KEYBOARD;
    if (have_pointer && this_impl->m_wl_pointer == nullptr) {
        this_impl->m_wl_pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(
            this_impl->m_wl_pointer,
            &m_wl_pointer_listener,
            this_impl
        );
    } else if (!have_pointer && this_impl->m_wl_pointer != nullptr) {
        wl_pointer_release(this_impl->m_wl_pointer);
        this_impl->m_wl_pointer = nullptr;
    }
    if (have_keyboard && this_impl->m_wl_keyboard == nullptr) {
        this_impl->m_wl_keyboard = wl_seat_get_keyboard(this_impl->m_wl_seat);
        wl_keyboard_add_listener(
            this_impl->m_wl_keyboard,
            &m_wl_keyboard_listener,
            this_impl
        );
    } else if (!have_keyboard && this_impl->m_wl_keyboard != nullptr) {
        wl_keyboard_release(this_impl->m_wl_keyboard);
        this_impl->m_wl_keyboard = nullptr;
    }
}

void core::window::detail::WaylandImpl::wl_seat_name(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_seat*    wl_seat,
    [[maybe_unused]] const char* name
) {
    [[maybe_unused]]
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    core::log::trace(std::format("{}", name));
}

void core::window::detail::WaylandImpl::wl_surface_draw_frame(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_callback* wl_callback,
    [[maybe_unused]] uint32_t     time
) {
    using core::math::numeric_cast;
    wl_callback_destroy(wl_callback);
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    wl_callback            = wl_surface_frame(this_impl->m_wl_surface);
    wl_callback_add_listener(
        wl_callback,
        &m_wl_surface_frame_listener,
        this_impl
    );
    this_impl->new_buffer(this_impl->m_size);
    wl_surface_attach(this_impl->m_wl_surface, this_impl->m_wl_buffer, 0, 0);
    wl_surface_damage_buffer(
        this_impl->m_wl_surface,
        0,
        0,
        numeric_cast<int32_t>(this_impl->m_size.x),
        numeric_cast<int32_t>(this_impl->m_size.y)
    );
    wl_surface_commit(this_impl->m_wl_surface);
    this_impl->m_last_frame = time;
}

void core::window::detail::WaylandImpl::xdg_surface_handle_configure(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] xdg_surface* xdg_surface,
    [[maybe_unused]] uint32_t     serial
) {
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    xdg_surface_ack_configure(xdg_surface, serial);
    if (this_impl->m_configured) {
        wl_surface_commit(this_impl->m_wl_surface);
    }
    this_impl->m_configured = true;
}

void core::window::detail::WaylandImpl::xdg_wm_base_handle_ping(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] xdg_wm_base* xdg_wm_base,
    [[maybe_unused]] uint32_t     serial
) {
    [[maybe_unused]]
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    xdg_wm_base_pong(xdg_wm_base, serial);
}

const wl_callback_listener
    core::window::detail::WaylandImpl::m_wl_surface_frame_listener{
        .done = wl_surface_draw_frame,
    };

const wl_keyboard_listener
    core::window::detail::WaylandImpl::m_wl_keyboard_listener = {
        .keymap      = wl_keyboard_keymap,
        .enter       = wl_keyboard_enter,
        .leave       = wl_keyboard_leave,
        .key         = wl_keyboard_key,
        .modifiers   = wl_keyboard_modifiers,
        .repeat_info = wl_keyboard_repeat_info,
};

const wl_pointer_listener
    core::window::detail::WaylandImpl::m_wl_pointer_listener = {
        .enter                   = wl_pointer_handle_enter,
        .leave                   = wl_pointer_handle_leave,
        .motion                  = wl_pointer_handle_motion,
        .button                  = wl_pointer_handle_button,
        .axis                    = wl_pointer_handle_axis,
        .frame                   = wl_pointer_handle_frame,
        .axis_source             = wl_pointer_handle_axis_source,
        .axis_stop               = wl_pointer_handle_axis_stop,
        .axis_discrete           = wl_pointer_handle_axis_discrete,
        .axis_value120           = wl_pointer_handle_axis_value120,
        .axis_relative_direction = wl_pointer_handle_axis_relative_direction,
};

const wl_registry_listener
    core::window::detail::WaylandImpl::m_wl_registry_listener = {
        .global        = wl_registry_handle_global,
        .global_remove = wl_registry_handle_global_remove,
};

const wl_seat_listener core::window::detail::WaylandImpl::m_wl_seat_listener = {
    .capabilities = wl_seat_handle_capabilities,
    .name         = wl_seat_name,
};

const xdg_surface_listener
    core::window::detail::WaylandImpl::m_xdg_surface_listener = {
        .configure = xdg_surface_handle_configure,
};

const xdg_wm_base_listener
    core::window::detail::WaylandImpl::m_xdg_wm_base_listener = {
        .ping = xdg_wm_base_handle_ping,
};
