#pragma once
#include "raygame/core/types.h"
#include "raygame/core/window/detail/wayland/keyboard.h"
#include "raygame/core/window/detail/wayland/pointers.h"
#include <wayland-client.h>

namespace core::window::detail {
class WaylandSeat {
    wl_seat*        m_wl_seat{nullptr};
    WaylandKeyboard m_keyboard;
    WaylandPointer  m_pointer;

    static void capabilities(void* data, wl_seat* seat, uint32_t capabilities);
    static void name(void* data, wl_seat* wl_seat, const char* name);

public:
    static const wl_seat_listener m_listener;
};
} // namespace core::window::detail
