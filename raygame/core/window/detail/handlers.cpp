#include "raygame/core/window/detail/handlers.h"
#include "raygame/core/window/window.h"

namespace {
using Impl = core::window::Window::Impl;
constexpr size_t BUF_SIZE{128};
} // namespace

// NOLINTBEGIN (bugprone-easily-swappable-parameters)
void KeyboardHandler::enter(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface,
    wl_array*                     keys
) {
    auto*                          self{static_cast<Impl*>(data)};
    const auto*                    keylist{static_cast<uint8_t*>(keys->data)};
    const std::span<const uint8_t> keyview{keylist, keys->size};
    std::array<char, BUF_SIZE>     buf{};
    for (const uint8_t key: keyview) {
        buf.fill(0);
        auto sym{self->m_keyboard.keysym(key, buf)};
        core::log::trace("sym: {} ({})", buf, sym);
    }
}

void KeyboardHandler::key(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     time,
    uint32_t                      key,
    uint32_t                      state
) {
    auto*                      self{static_cast<Impl*>(data)};
    std::array<char, BUF_SIZE> buf{};
    const auto                 sym{self->m_keyboard.keysym(key, buf)};
    const bool        is_pressed{(state == WL_KEYBOARD_KEY_STATE_PRESSED)};
    const std::string pr_str{is_pressed ? "press" : "release"};
    core::log::debug("key {}: sym: {} ({}), ", pr_str, buf.data(), sym);
}

void KeyboardHandler::keymap(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    uint32_t                      format,
    int32_t                       file_desc,
    uint32_t                      size
) {
    core::condition::pre_condition(
        format == WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1,
        "Invalid WL_KEYBOARD_KEYMAP_FORMAT"
    );
    auto* self{static_cast<Impl*>(data)};
    self->m_keyboard.set(file_desc, size);
}

void KeyboardHandler::leave(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface
) {
    core::log::trace("Keyboard Leave");
}

void KeyboardHandler::modifiers(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    uint32_t                      mods_depressed,
    uint32_t                      mods_latched,
    uint32_t                      mods_locked,
    uint32_t                      group
) {
    auto* self{static_cast<Impl*>(data)};
    self->m_keyboard.update(mods_depressed, mods_latched, mods_locked, group);
}

void KeyboardHandler::repeat_info(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] int32_t      rate,
    [[maybe_unused]] int32_t      delay
) {}

void PointerHandler::axis(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis,
    wl_fixed_t                   value
) {
    auto* self{static_cast<Impl*>(data)};
    self->m_pointer.m_event.event_mask |= POINTER_EVENT_AXIS;
    self->m_pointer.m_event.time        = time;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        self->m_pointer.m_event.axis_vertical.valid = true;
        self->m_pointer.m_event.axis_vertical.value = value;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        self->m_pointer.m_event.axis_horizontal.valid = true;
        self->m_pointer.m_event.axis_horizontal.value = value;
    } else {
        core::condition::unknown("axis");
    }
}

void PointerHandler::axis_discrete(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis,
    int32_t                      discrete
) {
    auto* self{static_cast<Impl*>(data)};
    self->m_pointer.m_event.event_mask |= POINTER_EVENT_AXIS_DISCRETE;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        self->m_pointer.m_event.axis_vertical.valid    = true;
        self->m_pointer.m_event.axis_vertical.discrete = discrete;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        self->m_pointer.m_event.axis_horizontal.valid    = true;
        self->m_pointer.m_event.axis_horizontal.discrete = discrete;
    } else {
        core::condition::unknown("axis");
    }
}

void PointerHandler::axis_relative_direction(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] uint32_t    direction
) {
    [[maybe_unused]]
    const Impl* const self{static_cast<Impl*>(data)};
}

void PointerHandler::axis_source(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis_source
) {
    auto* self{static_cast<Impl*>(data)};
    self->m_pointer.m_event.event_mask  |= POINTER_EVENT_AXIS_SOURCE;
    self->m_pointer.m_event.axis_source  = axis_source;
}

void PointerHandler::axis_stop(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis
) {
    auto* self{static_cast<Impl*>(data)};
    self->m_pointer.m_event.time        = time;
    self->m_pointer.m_event.event_mask |= POINTER_EVENT_AXIS_STOP;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        self->m_pointer.m_event.axis_vertical.valid = true;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        self->m_pointer.m_event.axis_horizontal.valid = true;
    } else {
        core::condition::unknown("axis");
    }
}

void PointerHandler::axis_value120(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] int32_t     value120
) {
    [[maybe_unused]]
    const Impl* const self{static_cast<Impl*>(data)};
}

void PointerHandler::button(
    void*                        data,
    [[maybe_unused]] wl_pointer* pointer,
    uint32_t                     serial,
    uint32_t                     time,
    uint32_t                     button,
    uint32_t                     state
) {
    auto* self{static_cast<Impl*>(data)};
    self->m_pointer.m_event.event_mask |= POINTER_EVENT_BUTTON;
    self->m_pointer.m_event.time        = time;
    self->m_pointer.m_event.serial      = serial;
    self->m_pointer.m_event.button      = button;
    self->m_pointer.m_event.state       = state;
}

void PointerHandler::enter(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     serial,
    [[maybe_unused]] wl_surface* surface,
    wl_fixed_t                   surface_x,
    wl_fixed_t                   surface_y
) {
    auto* self{static_cast<Impl*>(data)};
    self->m_pointer.m_event.event_mask |= POINTER_EVENT_ENTER;
    self->m_pointer.m_event.serial      = serial;
    self->m_pointer.m_event.surface_x   = surface_x;
    self->m_pointer.m_event.surface_y   = surface_y;
}

void PointerHandler::frame(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer
) {
    auto* self{static_cast<Impl*>(data)};
    auto& event = self->m_pointer.m_event;
    if ((event.event_mask & POINTER_EVENT_ENTER) != 0U) {
        core::log::trace(
            "Pointer Entry ({}, {})",
            wl_fixed_to_double(event.surface_x),
            wl_fixed_to_double(event.surface_y)
        );
    }
    if ((event.event_mask & POINTER_EVENT_LEAVE) != 0U) {
        core::log::trace("Pointer Leave");
    }
    if ((event.event_mask & POINTER_EVENT_MOTION) != 0U) {
        core::log::trace(
            "Pointer Motion ({}, {})",
            wl_fixed_to_double(event.surface_x),
            wl_fixed_to_double(event.surface_y)
        );
    }
    if ((event.event_mask & POINTER_EVENT_BUTTON) != 0U) {
        if ((event.state & WL_POINTER_BUTTON_STATE_PRESSED) != 0U) {
            core::log::trace("Button {} pressed", event.button);
        } else if ((event.state & WL_POINTER_BUTTON_STATE_RELEASED) != 0U) {
            core::log::trace("Button {} released", event.button);
        } else {
            core::condition::unknown("button state");
        }
    }
    if ((event.event_mask & ALL_AXIS_EVENTS) != 0U) {
        const auto handle_axis = [event](const axis_t& axis) {
            std::string ret_str = "Axis event:";
            if ((event.event_mask & POINTER_EVENT_AXIS) != 0U) {
                ret_str +=
                    std::format(" axis({}) ", wl_fixed_to_double(axis.value));
            }
            if ((event.event_mask & POINTER_EVENT_AXIS_DISCRETE) != 0U) {
                ret_str += std::format(" discrete({}) ", axis.discrete);
            }
            if ((event.event_mask & POINTER_EVENT_AXIS_SOURCE) != 0U) {
                ret_str += source_string(event.event_mask);
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
    event = {};
}

void PointerHandler::leave(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     serial,
    [[maybe_unused]] wl_surface* surface
) {
    auto* self{static_cast<Impl*>(data)};
    self->m_pointer.m_event.serial      = serial;
    self->m_pointer.m_event.event_mask |= POINTER_EVENT_LEAVE;
}

void PointerHandler::motion(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    wl_fixed_t                   surface_x,
    wl_fixed_t                   surface_y
) {
    auto* self{static_cast<Impl*>(data)};
    self->m_pointer.m_event.event_mask |= POINTER_EVENT_MOTION;
    self->m_pointer.m_event.time        = time;
    self->m_pointer.m_event.surface_x   = surface_x;
    self->m_pointer.m_event.surface_y   = surface_y;
}

void XdgWmBaseHandler::ping(
    void*        data,
    xdg_wm_base* xdg_wm_base,
    uint32_t     serial
) {
    [[maybe_unused]]
    auto* self{static_cast<Impl*>(data)};
    xdg_wm_base_pong(xdg_wm_base, serial);
}

void XdgToplevelHandler::configure(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t              width,
    [[maybe_unused]] int32_t              height,
    [[maybe_unused]] struct wl_array*     states
) {
    [[maybe_unused]]
    auto* self{static_cast<Impl*>(data)};
}

void XdgToplevelHandler::close(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel
) {
    auto* self{static_cast<Impl*>(data)};
    self->set_close();
}

void XdgToplevelHandler::configure_bounds(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t              width,
    [[maybe_unused]] int32_t              height
) {
    [[maybe_unused]]
    auto* self{static_cast<Impl*>(data)};
}

void XdgToplevelHandler::wm_capabilities(
    void*                                 data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] struct wl_array*     capabilities
) {
    [[maybe_unused]]
    auto* self{static_cast<Impl*>(data)};
}

void XdgSurfaceHandler::configure(
    void*        data,
    xdg_surface* xdg_surface,
    uint32_t     serial
) {
    auto* self{static_cast<Impl*>(data)};
    xdg_surface_ack_configure(xdg_surface, serial);
    if (self->m_configured) {
        self->m_surface.commit();
    }
    self->m_configured = true;
}

void SurfaceHandler::done(void* data, wl_callback* wl_callback, uint32_t time) {
    auto* self{static_cast<Impl*>(data)};
    wl_callback_destroy(wl_callback);
    wl_callback = wl_surface_frame(self->m_surface.wl_surface());
    wl_callback_add_listener(wl_callback, &listener, self);
    self->new_buffer();
    self->m_surface.attach(self->m_buffer, 0, 0);
    self->m_surface.damage({
        {0,                                                    0},
        {core::math::numeric_cast<int32_t>(self->buf_width()),
         core::math::numeric_cast<int32_t>(self->buf_height())  }
    });
    self->m_surface.commit();
    self->m_last_frame = time;
}

void SeatHandler::wl_seat_handle_capabilities(
    void*    data,
    wl_seat* seat,
    uint32_t capabilities
) {
    auto*      self{static_cast<Impl*>(data)};
    const bool have_pointer =
        (capabilities != 0U) && (WL_SEAT_CAPABILITY_POINTER != 0U);
    const bool have_keyboard =
        (capabilities & WL_SEAT_CAPABILITY_KEYBOARD) != 0U;
    if (have_pointer && !self->m_pointer.exists()) {
        self->m_pointer.bind(wl_seat_get_pointer(seat));
    } else if (!have_pointer && self->m_pointer.exists()) {
        self->m_pointer.add_listener(self);
        self->m_pointer.release();
    }
    if (have_keyboard && !self->m_keyboard.exists()) {
        self->m_keyboard.bind(wl_seat_get_keyboard(self->m_wl_seat));
        self->m_keyboard.add_listener(self);
    } else if (!have_keyboard && self->m_keyboard.exists()) {
        self->m_keyboard.release();
    }
}

void SeatHandler::wl_seat_name(
    void*                     data,
    [[maybe_unused]] wl_seat* wl_seat,
    const char*               name
) {
    [[maybe_unused]]
    auto* self{static_cast<Impl*>(data)};
    core::log::trace("{}", name);
}

void RegistryHandler::global(
    void*        data,
    wl_registry* registry,
    uint32_t     name,
    const char*  interface,
    uint32_t     version
) {
    auto*             self{static_cast<Impl*>(data)};
    const std::string interface_str{interface};
    if (interface_str == wl_shm_interface.name) {
        core::log::trace("Handled Global: {}", interface);
        self->m_buffer.bind(static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, version)
        ));
    } else if (interface_str == wl_compositor_interface.name) {
        core::log::trace("Handled Global: {}", interface);
        self->m_wl_compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, version)
        );
    } else if (interface_str == xdg_wm_base_interface.name) {
        core::log::trace("Handled Global: {}", interface);
        self->m_xdg_wm_base = static_cast<xdg_wm_base*>(
            wl_registry_bind(registry, name, &xdg_wm_base_interface, version)
        );
        xdg_wm_base_add_listener(
            self->m_xdg_wm_base,
            &XdgWmBaseHandler::listener,
            self
        );
    } else if (interface_str == wl_seat_interface.name) {
        core::log::trace("Handled Global: {}", interface);
        self->m_wl_seat = static_cast<wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface, version)
        );
        wl_seat_add_listener(self->m_wl_seat, &SeatHandler::listener, self);
    } else {
        core::log::trace("Unhandled Global: {}", interface);
    }
}

void RegistryHandler::remove(void* data, wl_registry* registry, uint32_t name) {
    [[maybe_unused]]
    auto* self{static_cast<Impl*>(data)};
    wl_registry_destroy(registry);
    core::log::trace("removed registry: {}", name);
}

// NOLINTEND (bugprone-easily-swappable-parameters)
