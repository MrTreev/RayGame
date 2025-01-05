#include "raygame/core/window/detail/wayland/pointers.h"
#include "raygame/core/condition.h"
#include "raygame/core/logger.h"
#include "raygame/core/types.h"

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

namespace core::window::detail {

const wl_pointer_listener WaylandPointer::m_listener{
    .enter                   = enter,
    .leave                   = leave,
    .motion                  = motion,
    .button                  = button,
    .axis                    = axis,
    .frame                   = frame,
    .axis_source             = axis_source,
    .axis_stop               = axis_stop,
    .axis_discrete           = axis_discrete,
    .axis_value120           = axis_value120,
    .axis_relative_direction = axis_relative_direction,
};

// NOLINTBEGIN(bugprone-easily-swappable-parameters)

void WaylandPointer::enter(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     serial,
    [[maybe_unused]] wl_surface* surface,
    wl_fixed_t                   surface_x,
    wl_fixed_t                   surface_y
) {
    auto* const self                  = static_cast<WaylandPointer*>(data);
    self->m_pointer_event.event_mask |= POINTER_EVENT_ENTER;
    self->m_pointer_event.serial      = serial;
    self->m_pointer_event.surface_x   = surface_x;
    self->m_pointer_event.surface_y   = surface_y;
}

void WaylandPointer::leave(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     serial,
    [[maybe_unused]] wl_surface* surface
) {
    auto* const self                  = static_cast<WaylandPointer*>(data);
    self->m_pointer_event.serial      = serial;
    self->m_pointer_event.event_mask |= POINTER_EVENT_LEAVE;
}

void WaylandPointer::motion(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    wl_fixed_t                   surface_x,
    wl_fixed_t                   surface_y
) {
    auto* self                        = static_cast<WaylandPointer*>(data);
    self->m_pointer_event.event_mask |= POINTER_EVENT_MOTION;
    self->m_pointer_event.time        = time;
    self->m_pointer_event.surface_x   = surface_x;
    self->m_pointer_event.surface_y   = surface_y;
}

void WaylandPointer::button(
    void*                        data,
    [[maybe_unused]] wl_pointer* pointer,
    uint32_t                     serial,
    uint32_t                     time,
    uint32_t                     button,
    uint32_t                     state
) {
    auto* const self                  = static_cast<WaylandPointer*>(data);
    self->m_pointer_event.event_mask |= POINTER_EVENT_BUTTON;
    self->m_pointer_event.time        = time;
    self->m_pointer_event.serial      = serial;
    self->m_pointer_event.button      = button;
    self->m_pointer_event.state       = state;
}

void WaylandPointer::axis(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis,
    wl_fixed_t                   value
) {
    auto* self                        = static_cast<WaylandPointer*>(data);
    self->m_pointer_event.event_mask |= POINTER_EVENT_AXIS;
    self->m_pointer_event.time        = time;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        self->m_pointer_event.axis_vertical.valid = true;
        self->m_pointer_event.axis_vertical.value = value;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        self->m_pointer_event.axis_horizontal.valid = true;
        self->m_pointer_event.axis_horizontal.value = value;
    } else {
        core::condition::unknown("axis");
    }
}

void WaylandPointer::frame(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer
) {
    const auto* const    self  = static_cast<WaylandPointer*>(data);
    const pointer_event& event = self->m_pointer_event;
    if ((event.event_mask & POINTER_EVENT_ENTER) != 0U) {
        log::trace(
            "Pointer Entry ({}, {})",
            wl_fixed_to_double(event.surface_x),
            wl_fixed_to_double(event.surface_y)
        );
    }
    if ((event.event_mask & POINTER_EVENT_LEAVE) != 0U) {
        log::trace("Pointer Leave");
    }
    if ((event.event_mask & POINTER_EVENT_MOTION) != 0U) {
        log::trace(
            "Pointer Motion ({}, {})",
            wl_fixed_to_double(event.surface_x),
            wl_fixed_to_double(event.surface_y)
        );
    }
    if ((event.event_mask & POINTER_EVENT_BUTTON) != 0U) {
        if ((event.state & WL_POINTER_BUTTON_STATE_PRESSED) != 0U) {
            log::trace("Button {} pressed", event.button);
        } else if ((event.state & WL_POINTER_BUTTON_STATE_RELEASED) != 0U) {
            log::trace("Button {} released", event.button);
        } else {
            condition::unknown("button state");
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
            log::trace(handle_axis(event.axis_horizontal));
        }
        if (event.axis_horizontal.valid) {
            log::trace(handle_axis(event.axis_vertical));
        }
    }
}

void WaylandPointer::axis_source(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis_source
) {
    auto* self                         = static_cast<WaylandPointer*>(data);
    self->m_pointer_event.event_mask  |= POINTER_EVENT_AXIS_SOURCE;
    self->m_pointer_event.axis_source  = axis_source;
}

void WaylandPointer::axis_stop(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     time,
    uint32_t                     axis
) {
    auto* self                        = static_cast<WaylandPointer*>(data);
    self->m_pointer_event.time        = time;
    self->m_pointer_event.event_mask |= POINTER_EVENT_AXIS_STOP;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        self->m_pointer_event.axis_vertical.valid = true;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        self->m_pointer_event.axis_horizontal.valid = true;
    } else {
        core::condition::unknown("axis");
    }
}

void WaylandPointer::axis_discrete(
    void*                        data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    uint32_t                     axis,
    int32_t                      discrete
) {
    auto* self                        = static_cast<WaylandPointer*>(data);
    self->m_pointer_event.event_mask |= POINTER_EVENT_AXIS_DISCRETE;
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
        self->m_pointer_event.axis_vertical.valid    = true;
        self->m_pointer_event.axis_vertical.discrete = discrete;
    } else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
        self->m_pointer_event.axis_horizontal.valid    = true;
        self->m_pointer_event.axis_horizontal.discrete = discrete;
    } else {
        core::condition::unknown("axis");
    }
}

void WaylandPointer::axis_value120(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] int32_t     value120
) {}

void WaylandPointer::axis_relative_direction(
    [[maybe_unused]] void*       data,
    [[maybe_unused]] wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t    axis,
    [[maybe_unused]] uint32_t    direction
) {}

} // namespace core::window::detail

// NOLINTEND(bugprone-easily-swappable-parameters)
