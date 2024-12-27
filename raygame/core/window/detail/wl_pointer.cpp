#include "raygame/core/logger.h"
#include "raygame/core/window/detail/wayland.h"

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

} // namespace

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
        core::log::trace(
            "Pointer Entry ({}, {})",
            wl_fixed_to_double(event.surface_x),
            wl_fixed_to_double(event.surface_y)
        );
    }
    if (event.event_mask & POINTER_EVENT_LEAVE) {
        core::log::trace("Pointer Leave");
    }
    if (event.event_mask & POINTER_EVENT_MOTION) {
        core::log::trace(
            "Pointer Motion ({}, {})",
            wl_fixed_to_double(event.surface_x),
            wl_fixed_to_double(event.surface_y)
        );
    }
    if (event.event_mask & POINTER_EVENT_BUTTON) {
        if (event.state & WL_POINTER_BUTTON_STATE_PRESSED) {
            core::log::trace("Button {} pressed", event.button);
        } else if (event.state & WL_POINTER_BUTTON_STATE_RELEASED) {
            core::log::trace("Button {} released", event.button);
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
    event = {};
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
