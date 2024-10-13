#include "core/condition.h"
#include "core/logger.h"
#include "core/math.h"
#include "core/windowimpl/wayland.h"
#include <cstring>
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include <xdg-shell-client-protocol.h>
#include <xkbcommon/xkbcommon.h>

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

struct axis_t {
    bool       valid;
    wl_fixed_t value;
    int32_t    discrete;
};
} // namespace

struct core::window::WaylandWindow::pointer_event {
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

struct core::window::WaylandWindow::keyboard_state {
    xkb_state*   xkb_state;
    xkb_context* xkb_context;
    xkb_keymap*  xkb_keymap;
};

void core::window::WaylandWindow::init_pointer_event() {
    m_pointer_event = new pointer_event();
}

void core::window::WaylandWindow::destroy_pointer_event() {
    delete m_pointer_event;
}

void core::window::WaylandWindow::init_keyboard_state() {
    m_keyboard_state              = new keyboard_state();
    m_keyboard_state->xkb_context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
}

void core::window::WaylandWindow::destroy_keyboard_state() {
    delete m_keyboard_state;
}

void core::window::WaylandWindow::wl_keyboard_enter(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface,
    [[maybe_unused]] wl_array*    keys
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    for (size_t i = 0; i > keys->size; ++i) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
        char key = static_cast<char*>(keys->data)[i];
#pragma clang diagnostic pop
        std::array<char, 128> buf;
        xkb_keysym_t          sym = xkb_state_key_get_one_sym(
            thiswindow->m_keyboard_state->xkb_state,
            static_cast<xkb_keycode_t>(key + 8)
        );
        xkb_keysym_get_name(sym, buf.data(), buf.size());
        log::trace(std::format("sym: {} ({})", buf.data(), sym));
    }
}

void core::window::WaylandWindow::wl_keyboard_key(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     time,
    [[maybe_unused]] uint32_t     key,
    [[maybe_unused]] uint32_t     state
) {
    WaylandWindow*        thiswindow = static_cast<WaylandWindow*>(data);
    std::array<char, 128> buf;
    uint32_t              keycode = key + 8;
    xkb_keysym_t          sym     = xkb_state_key_get_one_sym(
        thiswindow->m_keyboard_state->xkb_state,
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

void core::window::WaylandWindow::wl_keyboard_keymap(
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
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    char*          map_shm =
        static_cast<char*>(mmap(nullptr, size, PROT_READ, MAP_SHARED, fd, 0));
    core::condition::check_condition(
        map_shm != MAP_FAILED,
        "Failed keyboard shm map"
    );
    xkb_keymap* xkb_keymap = xkb_keymap_new_from_string(
        thiswindow->m_keyboard_state->xkb_context,
        map_shm,
        XKB_KEYMAP_FORMAT_TEXT_V1,
        XKB_KEYMAP_COMPILE_NO_FLAGS
    );
    core::condition::check_ptr(xkb_keymap, "Failed to create new xkb_keymap");
    munmap(map_shm, size);
    close(fd);
    xkb_state* xkb_state = xkb_state_new(xkb_keymap);
    core::condition::check_ptr(xkb_state, "Failed to create new xkb_state");
    xkb_keymap_unref(thiswindow->m_keyboard_state->xkb_keymap);
    xkb_state_unref(thiswindow->m_keyboard_state->xkb_state);
    thiswindow->m_keyboard_state->xkb_keymap = xkb_keymap;
    thiswindow->m_keyboard_state->xkb_state  = xkb_state;
}

void core::window::WaylandWindow::wl_keyboard_leave(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface
) {
    core::log::trace("Keyboard Leave");
}

void core::window::WaylandWindow::wl_keyboard_modifiers(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     mods_depressed,
    [[maybe_unused]] uint32_t     mods_latched,
    [[maybe_unused]] uint32_t     mods_locked,
    [[maybe_unused]] uint32_t     group
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    xkb_state_update_mask(
        thiswindow->m_keyboard_state->xkb_state,
        mods_depressed,
        mods_latched,
        mods_locked,
        0,
        0,
        group
    );
}

void core::window::WaylandWindow::wl_keyboard_repeat_info(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] int32_t      rate,
    [[maybe_unused]] int32_t      delay
) {}

void core::window::WaylandWindow::wl_pointer_handle_axis(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    time,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] wl_fixed_t  value
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    thiswindow->m_pointer_event->event_mask |= POINTER_EVENT_AXIS;
    thiswindow->m_pointer_event->time        = time;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        thiswindow->m_pointer_event->axis_vertical.valid = true;
        thiswindow->m_pointer_event->axis_vertical.value = value;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        thiswindow->m_pointer_event->axis_horizontal.valid = true;
        thiswindow->m_pointer_event->axis_horizontal.value = value;
    }
    RG_ELSE_UNKNOWN("axis");
}

void core::window::WaylandWindow::wl_pointer_handle_axis_discrete(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] int32_t     discrete
) {
    [[maybe_unused]]
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    thiswindow->m_pointer_event->event_mask |= POINTER_EVENT_AXIS_DISCRETE;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        thiswindow->m_pointer_event->axis_vertical.valid    = true;
        thiswindow->m_pointer_event->axis_vertical.discrete = discrete;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        thiswindow->m_pointer_event->axis_horizontal.valid    = true;
        thiswindow->m_pointer_event->axis_horizontal.discrete = discrete;
    }
    RG_ELSE_UNKNOWN("axis");
}

void core::window::WaylandWindow::wl_pointer_handle_axis_relative_direction(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] uint32_t    direction
) {
    [[maybe_unused]]
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
}

void core::window::WaylandWindow::wl_pointer_handle_axis_source(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis_source
) {
    [[maybe_unused]]
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    thiswindow->m_pointer_event->event_mask  |= POINTER_EVENT_AXIS_SOURCE;
    thiswindow->m_pointer_event->axis_source  = axis_source;
}

void core::window::WaylandWindow::wl_pointer_handle_axis_stop(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis
) {
    [[maybe_unused]]
    WaylandWindow* thiswindow         = static_cast<WaylandWindow*>(data);
    thiswindow->m_pointer_event->time = time;
    thiswindow->m_pointer_event->event_mask |= POINTER_EVENT_AXIS_STOP;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        thiswindow->m_pointer_event->axis_vertical.valid = true;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        thiswindow->m_pointer_event->axis_horizontal.valid = true;
    }
    RG_ELSE_UNKNOWN("axis");
}

void core::window::WaylandWindow::wl_pointer_handle_axis_value120(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] int32_t     value120
) {
    [[maybe_unused]]
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
}

void core::window::WaylandWindow::wl_pointer_handle_button(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* pointer,
    [[maybe_unused]] uint32_t    serial,
    [[maybe_unused]] uint32_t    time,
    [[maybe_unused]] uint32_t    button,
    [[maybe_unused]] uint32_t    state
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    thiswindow->m_pointer_event->event_mask |= POINTER_EVENT_BUTTON;
    thiswindow->m_pointer_event->time        = time;
    thiswindow->m_pointer_event->serial      = serial;
    thiswindow->m_pointer_event->button      = button;
    thiswindow->m_pointer_event->state       = state;
}

void core::window::WaylandWindow::wl_pointer_handle_enter(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    serial,
    [[maybe_unused]] wl_surface* surface,
    [[maybe_unused]] wl_fixed_t  surface_x,
    [[maybe_unused]] wl_fixed_t  surface_y
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    thiswindow->m_pointer_event->event_mask |= POINTER_EVENT_ENTER;
    thiswindow->m_pointer_event->serial      = serial;
    thiswindow->m_pointer_event->surface_x   = surface_x;
    thiswindow->m_pointer_event->surface_y   = surface_y;
}

void core::window::WaylandWindow::wl_pointer_handle_frame(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    pointer_event* event      = thiswindow->m_pointer_event;
    if (event->event_mask & POINTER_EVENT_ENTER) {
        core::log::trace(std::format(
            "Pointer Entry ({}, {})",
            wl_fixed_to_double(event->surface_x),
            wl_fixed_to_double(event->surface_y)
        ));
    }
    if (event->event_mask & POINTER_EVENT_LEAVE) {
        core::log::trace("Pointer Leave");
    }
    if (event->event_mask & POINTER_EVENT_MOTION) {
        core::log::trace(std::format(
            "Pointer Motion ({}, {})",
            wl_fixed_to_double(event->surface_x),
            wl_fixed_to_double(event->surface_y)
        ));
    }
    if (event->event_mask & POINTER_EVENT_BUTTON) {
        if (event->state & WL_POINTER_BUTTON_STATE_PRESSED) {
            core::log::trace(std::format("Button {} pressed", event->button));
        } else if (event->state & WL_POINTER_BUTTON_STATE_RELEASED) {
            core::log::trace(std::format("Button {} released", event->button));
        }
        RG_ELSE_UNKNOWN("button state");
    }
    if (event->event_mask & ALL_AXIS_EVENTS) {
        const auto handle_axis = [event](const axis_t& axis) {
            std::string ret_str = "Axis event:";
            if (event->event_mask & POINTER_EVENT_AXIS) {
                ret_str +=
                    std::format(" axis({}) ", wl_fixed_to_double(axis.value));
            }
            if (event->event_mask & POINTER_EVENT_AXIS_DISCRETE) {
                ret_str += std::format(" discrete({}) ", axis.discrete);
            }
            if (event->event_mask & POINTER_EVENT_AXIS_SOURCE) {
                if (event->axis_source == WL_POINTER_AXIS_SOURCE_WHEEL) {
                    ret_str += std::format(" source(wheel) ");
                } else if (event->axis_source
                           == WL_POINTER_AXIS_SOURCE_FINGER) {
                    ret_str += std::format(" source(finger) ");
                } else if (event->axis_source
                           == WL_POINTER_AXIS_SOURCE_CONTINUOUS) {
                    ret_str += std::format(" source(continuous) ");
                } else if (event->axis_source
                           == WL_POINTER_AXIS_SOURCE_WHEEL_TILT) {
                    ret_str += std::format(" source(wheel tilt) ");
                }
                RG_ELSE_UNKNOWN("axis source");
            }
            return ret_str;
        };
        if (event->axis_vertical.valid) {
            core::log::trace(handle_axis(event->axis_horizontal));
        }
        if (event->axis_horizontal.valid) {
            core::log::trace(handle_axis(event->axis_vertical));
        }
    }
    std::memset(event, 0, sizeof(*event));
}

void core::window::WaylandWindow::wl_pointer_handle_leave(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    serial,
    [[maybe_unused]] wl_surface* surface
) {
    WaylandWindow* thiswindow           = static_cast<WaylandWindow*>(data);
    thiswindow->m_pointer_event->serial = serial;
    thiswindow->m_pointer_event->event_mask |= POINTER_EVENT_LEAVE;
}

void core::window::WaylandWindow::wl_pointer_handle_motion(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    time,
    [[maybe_unused]] wl_fixed_t  surface_x,
    [[maybe_unused]] wl_fixed_t  surface_y
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    thiswindow->m_pointer_event->event_mask |= POINTER_EVENT_MOTION;
    thiswindow->m_pointer_event->time        = time;
    thiswindow->m_pointer_event->surface_x   = surface_x;
    thiswindow->m_pointer_event->surface_y   = surface_y;
}

void core::window::WaylandWindow::wl_registry_handle_global(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_registry* registry,
    [[maybe_unused]] uint32_t     name,
    [[maybe_unused]] const char*  interface,
    [[maybe_unused]] uint32_t     version
) {
    WaylandWindow*    thiswindow = static_cast<WaylandWindow*>(data);
    const std::string interface_str{interface};
    if (interface_str == wl_shm_interface.name) {
        core::log::trace(std::format("Handled Global: {}", interface));
        thiswindow->m_wl_shm = static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, version)
        );
    } else if (interface_str == wl_compositor_interface.name) {
        core::log::trace(std::format("Handled Global: {}", interface));
        thiswindow->m_wl_compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, version)
        );
    } else if (interface_str == xdg_wm_base_interface.name) {
        core::log::trace(std::format("Handled Global: {}", interface));
        thiswindow->m_xdg_wm_base = static_cast<xdg_wm_base*>(
            wl_registry_bind(registry, name, &xdg_wm_base_interface, version)
        );
        xdg_wm_base_add_listener(
            thiswindow->m_xdg_wm_base,
            &m_xdg_wm_base_listener,
            thiswindow
        );
    } else if (interface_str == wl_seat_interface.name) {
        core::log::trace(std::format("Handled Global: {}", interface));
        thiswindow->m_wl_seat = static_cast<wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface, version)
        );
        wl_seat_add_listener(
            thiswindow->m_wl_seat,
            &m_wl_seat_listener,
            thiswindow
        );
    } else {
        core::log::trace(std::format("Unhandled Global: {}", interface));
    }
}

void core::window::WaylandWindow::wl_registry_handle_global_remove(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_registry* registry,
    [[maybe_unused]] uint32_t     name
) {
    [[maybe_unused]]
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    wl_registry_destroy(registry);
    core::log::trace(std::format("removed registry: {}", name));
}

void core::window::WaylandWindow::wl_seat_handle_capabilities(
    [[maybe_unused]] void*    data,
    [[maybe_unused]] wl_seat* seat,
    [[maybe_unused]] uint32_t capabilities
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    bool have_pointer  = (capabilities != 0U) && WL_SEAT_CAPABILITY_POINTER;
    bool have_keyboard = capabilities & WL_SEAT_CAPABILITY_KEYBOARD;
    if (have_pointer && thiswindow->m_wl_pointer == nullptr) {
        thiswindow->m_wl_pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(
            thiswindow->m_wl_pointer,
            &m_wl_pointer_listener,
            thiswindow
        );
    } else if (!have_pointer && thiswindow->m_wl_pointer != nullptr) {
        wl_pointer_release(thiswindow->m_wl_pointer);
        thiswindow->m_wl_pointer = nullptr;
    }
    if (have_keyboard && thiswindow->m_wl_keyboard == nullptr) {
        thiswindow->m_wl_keyboard = wl_seat_get_keyboard(thiswindow->m_wl_seat);
        wl_keyboard_add_listener(
            thiswindow->m_wl_keyboard,
            &m_wl_keyboard_listener,
            thiswindow
        );
    } else if (!have_keyboard && thiswindow->m_wl_keyboard != nullptr) {
        wl_keyboard_release(thiswindow->m_wl_keyboard);
        thiswindow->m_wl_keyboard = nullptr;
    }
}

void core::window::WaylandWindow::wl_seat_name(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_seat*    wl_seat,
    [[maybe_unused]] const char* name
) {
    [[maybe_unused]]
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    core::log::trace(std::format("{}", name));
}

void core::window::WaylandWindow::wl_surface_draw_frame(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_callback* wl_callback,
    [[maybe_unused]] uint32_t     time
) {
    using core::math::numeric_cast;
    wl_callback_destroy(wl_callback);
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    wl_callback               = wl_surface_frame(thiswindow->m_wl_surface);
    wl_callback_add_listener(
        wl_callback,
        &m_wl_surface_frame_listener,
        thiswindow
    );
    thiswindow->new_buffer();
    wl_surface_attach(thiswindow->m_wl_surface, thiswindow->m_wl_buffer, 0, 0);
    wl_surface_damage_buffer(
        thiswindow->m_wl_surface,
        0,
        0,
        numeric_cast<int32_t>(thiswindow->m_size.x),
        numeric_cast<int32_t>(thiswindow->m_size.y)
    );
    wl_surface_commit(thiswindow->m_wl_surface);
    thiswindow->m_last_frame = time;
}

void core::window::WaylandWindow::xdg_surface_handle_configure(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] xdg_surface* xdg_surface,
    [[maybe_unused]] uint32_t     serial
) {
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    xdg_surface_ack_configure(xdg_surface, serial);
    if (thiswindow->m_configured) {
        wl_surface_commit(thiswindow->m_wl_surface);
    }
    thiswindow->m_configured = true;
}

void core::window::WaylandWindow::xdg_wm_base_handle_ping(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] xdg_wm_base* xdg_wm_base,
    [[maybe_unused]] uint32_t     serial
) {
    [[maybe_unused]]
    WaylandWindow* thiswindow = static_cast<WaylandWindow*>(data);
    xdg_wm_base_pong(xdg_wm_base, serial);
}

const wl_callback_listener
    core::window::WaylandWindow::m_wl_surface_frame_listener{
        .done = wl_surface_draw_frame,
    };

const wl_keyboard_listener core::window::WaylandWindow::m_wl_keyboard_listener =
    {
        .keymap      = wl_keyboard_keymap,
        .enter       = wl_keyboard_enter,
        .leave       = wl_keyboard_leave,
        .key         = wl_keyboard_key,
        .modifiers   = wl_keyboard_modifiers,
        .repeat_info = wl_keyboard_repeat_info,
};

const wl_pointer_listener core::window::WaylandWindow::m_wl_pointer_listener = {
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

const wl_registry_listener core::window::WaylandWindow::m_wl_registry_listener =
    {
        .global        = wl_registry_handle_global,
        .global_remove = wl_registry_handle_global_remove,
};

const wl_seat_listener core::window::WaylandWindow::m_wl_seat_listener = {
    .capabilities = wl_seat_handle_capabilities,
    .name         = wl_seat_name,
};

const xdg_surface_listener core::window::WaylandWindow::m_xdg_surface_listener =
    {
        .configure = xdg_surface_handle_configure,
};

const xdg_wm_base_listener core::window::WaylandWindow::m_xdg_wm_base_listener =
    {
        .ping = xdg_wm_base_handle_ping,
};
