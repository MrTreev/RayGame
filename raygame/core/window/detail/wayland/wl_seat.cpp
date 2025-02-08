#include "raygame/core/window/detail/wayland.h"
#if defined(RAYGAME_GUI_BACKEND_WAYLAND)
#    include "raygame/core/logger.h"
#    include <wayland-client-protocol.h>

const wl_seat_listener
    core::window::detail::WaylandWindowImpl::m_wl_seat_listener = {
        .capabilities = wl_seat_handle_capabilities,
        .name         = wl_seat_name,
};

void core::window::detail::WaylandWindowImpl::wl_seat_handle_capabilities(
    void*    data,
    wl_seat* seat,
    uint32_t capabilities
) {
    auto*      this_impl = static_cast<WaylandWindowImpl*>(data);
    const bool have_pointer =
        (capabilities != 0U) && (WL_SEAT_CAPABILITY_POINTER != 0U);
    const bool have_keyboard =
        (capabilities & WL_SEAT_CAPABILITY_KEYBOARD) != 0U;
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

void core::window::detail::WaylandWindowImpl::wl_seat_name(
    void*                     data,
    [[maybe_unused]] wl_seat* wl_seat,
    const char*               name
) {
    [[maybe_unused]]
    auto* this_impl = static_cast<WaylandWindowImpl*>(data);
    core::log::trace("{}", name);
}
#endif
