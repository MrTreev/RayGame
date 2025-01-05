#include "raygame/core/window/detail/wayland/seat.h"
#include <wayland-client-protocol.h>

namespace core::window::detail {
const wl_seat_listener WaylandSeat::m_listener{
    .capabilities = capabilities,
    .name         = name,
};

namespace {
bool has_keyboard(uint32_t capabilities) {
    return (capabilities & WL_SEAT_CAPABILITY_KEYBOARD) != 0U;
}

bool has_pointer(uint32_t capabilities) {
    return (capabilities != 0U) && (WL_SEAT_CAPABILITY_POINTER != 0U);
}
} // namespace

void WaylandSeat::capabilities(
    void*    data,
    wl_seat* seat,
    uint32_t capabilities
) {
    auto* this_impl     = static_cast<WaylandSeat*>(data);
    bool  have_keyboard = (capabilities & WL_SEAT_CAPABILITY_KEYBOARD) != 0U;
    if (has_pointer(capabilities) && this_impl->m_wl_pointer == nullptr) {
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

void WaylandSeat::name(void* data, wl_seat* wl_seat, const char* name) {}
} // namespace core::window::detail
