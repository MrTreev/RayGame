#include "raygame/core/window/detail/wayland.h"
#if defined(RAYGAME_GUI_BACKEND_WAYLAND)
#    include "raygame/core/condition.h"
#    include "raygame/core/logger.h"
#    include <wayland-client-protocol.h>

const wl_pointer_listener core::window::detail::WaylandWindowImpl::m_wl_pointer_listener = {
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

} // namespace

// NOLINTBEGIN(*-easily-swappable-parameters)
void core::window::detail::WaylandWindowImpl::wl_pointer_handle_axis(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis,
    wl_fixed_t                   value
) {
    auto* this_impl                        = static_cast<WaylandWindowImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_AXIS;
    this_impl->m_pointer_event.time        = time;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        this_impl->m_pointer_event.axis_vertical.valid = true;
        this_impl->m_pointer_event.axis_vertical.value = value;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        this_impl->m_pointer_event.axis_horizontal.valid = true;
        this_impl->m_pointer_event.axis_horizontal.value = value;
    } else {
        core::condition::unknown("axis");
    }
}

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_axis_discrete(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis,
    int32_t                      discrete
) {
    auto* this_impl                        = static_cast<WaylandWindowImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_AXIS_DISCRETE;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        this_impl->m_pointer_event.axis_vertical.valid    = true;
        this_impl->m_pointer_event.axis_vertical.discrete = discrete;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        this_impl->m_pointer_event.axis_horizontal.valid    = true;
        this_impl->m_pointer_event.axis_horizontal.discrete = discrete;
    } else {
        core::condition::unknown("axis");
    }
}

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_axis_relative_direction(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] uint32_t    direction
) {
    [[maybe_unused]]
    const WaylandWindowImpl* const this_impl = static_cast<WaylandWindowImpl*>(data);
}

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_axis_source(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis_source
) {
    auto* this_impl                         = static_cast<WaylandWindowImpl*>(data);
    this_impl->m_pointer_event.event_mask  |= POINTER_EVENT_AXIS_SOURCE;
    this_impl->m_pointer_event.axis_source  = axis_source;
}

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_axis_stop(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis
) {
    auto* this_impl                        = static_cast<WaylandWindowImpl*>(data);
    this_impl->m_pointer_event.time        = time;
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_AXIS_STOP;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        this_impl->m_pointer_event.axis_vertical.valid = true;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        this_impl->m_pointer_event.axis_horizontal.valid = true;
    } else {
        core::condition::unknown("axis");
    }
}

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_axis_value120(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] int32_t     value120
) {
    [[maybe_unused]]
    const WaylandWindowImpl* const this_impl = static_cast<WaylandWindowImpl*>(data);
}

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_button(
    void*                        data,
    [[maybe_unused]] wl_pointer* pointer,
    uint32_t                     serial,
    uint32_t                     time,
    uint32_t                     button,
    uint32_t                     state
) {
    auto* this_impl                        = static_cast<WaylandWindowImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_BUTTON;
    this_impl->m_pointer_event.time        = time;
    this_impl->m_pointer_event.serial      = serial;
    this_impl->m_pointer_event.button      = button;
    this_impl->m_pointer_event.state       = state;
}

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_enter(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     serial,
    [[maybe_unused]] wl_surface* surface,
    wl_fixed_t                   surface_x,
    wl_fixed_t                   surface_y
) {
    auto* this_impl                        = static_cast<WaylandWindowImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_ENTER;
    this_impl->m_pointer_event.serial      = serial;
    this_impl->m_pointer_event.surface_x   = surface_x;
    this_impl->m_pointer_event.surface_y   = surface_y;
}

namespace {
std::string source_string(uint32_t axis_source) {
    switch (axis_source) {
    case WL_POINTER_AXIS_SOURCE_WHEEL:      return " source(wheel) ";
    case WL_POINTER_AXIS_SOURCE_FINGER:     return " source(finger) ";
    case WL_POINTER_AXIS_SOURCE_CONTINUOUS: return " source(continuous) ";
    case WL_POINTER_AXIS_SOURCE_WHEEL_TILT: return " source(wheel tilt) ";
    default:                                return " ";
    }
}
} // namespace

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_frame(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer
) {
    const auto*         this_impl = static_cast<WaylandWindowImpl*>(data);
    const PointerEvent& event     = this_impl->m_pointer_event;
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
        if (event.state == WL_POINTER_BUTTON_STATE_PRESSED) {
            core::log::trace(
                "Button {} pressed at {}",
                event.button,
                std::string(
                    core::Vec2<double>(
                        wl_fixed_to_double(event.surface_x),
                        wl_fixed_to_double(event.surface_y)
                    )
                )
            );
        } else if (event.state == WL_POINTER_BUTTON_STATE_RELEASED) {
            core::log::trace("Button {} released", event.button);
        } else {
            core::log::error("Button {}", event.button);
            core::log::error("State  {}", event.state);
            core::condition::unknown("button state");
        }
    }
    if ((event.event_mask & ALL_AXIS_EVENTS) != 0U) {
        const auto handle_axis = [event](const Axis& axis) {
            std::string ret_str = "Axis event:";
            if ((event.event_mask & POINTER_EVENT_AXIS) != 0U) {
                ret_str += std::format(" axis({}) ", wl_fixed_to_double(axis.value));
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
}

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_leave(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     serial,
    [[maybe_unused]] wl_surface* surface
) {
    auto* this_impl                        = static_cast<WaylandWindowImpl*>(data);
    this_impl->m_pointer_event.serial      = serial;
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_LEAVE;
}

void core::window::detail::WaylandWindowImpl::wl_pointer_handle_motion(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    wl_fixed_t                   surface_x,
    wl_fixed_t                   surface_y
) {
    auto* this_impl                        = static_cast<WaylandWindowImpl*>(data);
    this_impl->m_pointer_event.event_mask |= POINTER_EVENT_MOTION;
    this_impl->m_pointer_event.time        = time;
    this_impl->m_pointer_event.surface_x   = surface_x;
    this_impl->m_pointer_event.surface_y   = surface_y;
}

// NOLINTEND(*-easily-swappable-parameters)
#endif
