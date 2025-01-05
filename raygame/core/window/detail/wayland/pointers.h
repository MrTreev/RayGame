#pragma once
#include "raygame/core/types.h"
#include <wayland-client-protocol.h>

namespace core::window::detail {
class WaylandPointer {
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
        time_t     time;
        uint32_t   serial;
        axis_t     axis_vertical;
        axis_t     axis_horizontal;
        uint32_t   axis_source;
    };

    pointer_event m_pointer_event{};
    wl_pointer*   m_wl_pointer = nullptr;

    static void enter(
        void*       data,
        wl_pointer* wl_pointer,
        uint32_t    serial,
        wl_surface* surface,
        wl_fixed_t  surface_x,
        wl_fixed_t  surface_y
    );

    static void leave(
        void*       data,
        wl_pointer* wl_pointer,
        uint32_t    serial,
        wl_surface* surface
    );

    static void motion(
        void*       data,
        wl_pointer* wl_pointer,
        uint32_t    time,
        wl_fixed_t  surface_x,
        wl_fixed_t  surface_y
    );

    static void button(
        void*       data,
        wl_pointer* pointer,
        uint32_t    serial,
        uint32_t    time,
        uint32_t    button,
        uint32_t    state
    );

    static void axis(
        void*       data,
        wl_pointer* wl_pointer,
        uint32_t    time,
        uint32_t    axis,
        wl_fixed_t  value
    );

    static void frame(void* data, wl_pointer* wl_pointer);

    static void
    axis_source(void* data, wl_pointer* wl_pointer, uint32_t axis_source);

    static void
    axis_stop(void* data, wl_pointer* wl_pointer, uint32_t time, uint32_t axis);

    static void axis_discrete(
        void*       data,
        wl_pointer* wl_pointer,
        uint32_t    axis,
        int32_t     discrete
    );

    static void axis_value120(
        void*       data,
        wl_pointer* wl_pointer,
        uint32_t    axis,
        int32_t     value120
    );

    static void axis_relative_direction(
        void*       data,
        wl_pointer* wl_pointer,
        uint32_t    axis,
        uint32_t    direction
    );

public:
    static const wl_pointer_listener m_listener;
};
} // namespace core::window::detail
