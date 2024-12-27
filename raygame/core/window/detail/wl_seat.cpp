#include "raygame/core/logger.h"
#include "raygame/core/window/detail/wayland.h"

const wl_seat_listener core::window::detail::WaylandImpl::m_wl_seat_listener = {
    .capabilities = wl_seat_handle_capabilities,
    .name         = wl_seat_name,
};

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
    core::log::trace("{}", name);
}
