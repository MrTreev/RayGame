#include "raygame/core/logger.h"
#include "raygame/core/window/detail/wayland.h"
#include <sys/mman.h>
#include <unistd.h>

const wl_keyboard_listener
    core::window::detail::WaylandImpl::m_wl_keyboard_listener = {
        .keymap      = wl_keyboard_keymap,
        .enter       = wl_keyboard_enter,
        .leave       = wl_keyboard_leave,
        .key         = wl_keyboard_key,
        .modifiers   = wl_keyboard_modifiers,
        .repeat_info = wl_keyboard_repeat_info,
};

void core::window::detail::WaylandImpl::wl_keyboard_enter(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface,
    [[maybe_unused]] wl_array*    keys
) {
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    for (size_t i = 0; i > keys->size; ++i) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
        char key = static_cast<char*>(keys->data)[i];
#pragma clang diagnostic pop
        std::array<char, 128> buf;
        xkb_keysym_t          sym = xkb_state_key_get_one_sym(
            this_impl->m_keyboard_state.m_xkb_state,
            static_cast<xkb_keycode_t>(key + 8)
        );
        xkb_keysym_get_name(sym, buf.data(), buf.size());
        log::trace("sym: {} ({})", buf.data(), sym);
    }
}

void core::window::detail::WaylandImpl::wl_keyboard_key(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     time,
    [[maybe_unused]] uint32_t     key,
    [[maybe_unused]] uint32_t     state
) {
    WaylandImpl*          this_impl = static_cast<WaylandImpl*>(data);
    std::array<char, 128> buf;
    uint32_t              keycode = key + 8;
    xkb_keysym_t          sym     = xkb_state_key_get_one_sym(
        this_impl->m_keyboard_state.m_xkb_state,
        keycode
    );
    xkb_keysym_get_name(sym, buf.data(), sizeof(buf));
    log::debug(
        "key {}: sym: {} ({}), ",
        (state == WL_KEYBOARD_KEY_STATE_PRESSED) ? "press" : "release",
        buf.data(),
        sym
    );
}

void core::window::detail::WaylandImpl::wl_keyboard_keymap(
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
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    char*        map_shm =
        static_cast<char*>(mmap(nullptr, size, PROT_READ, MAP_SHARED, fd, 0));
    core::condition::check_condition(
        map_shm != MAP_FAILED,
        "Failed keyboard shm map"
    );
    xkb_keymap* xkb_keymap = xkb_keymap_new_from_string(
        this_impl->m_keyboard_state.m_xkb_context,
        map_shm,
        XKB_KEYMAP_FORMAT_TEXT_V1,
        XKB_KEYMAP_COMPILE_NO_FLAGS
    );
    core::condition::check_ptr(xkb_keymap, "Failed to create new xkb_keymap");
    munmap(map_shm, size);
    close(fd);
    xkb_state* xkb_state = xkb_state_new(xkb_keymap);
    core::condition::check_ptr(xkb_state, "Failed to create new xkb_state");
    xkb_keymap_unref(this_impl->m_keyboard_state.m_xkb_keymap);
    xkb_state_unref(this_impl->m_keyboard_state.m_xkb_state);
    this_impl->m_keyboard_state.m_xkb_keymap = xkb_keymap;
    this_impl->m_keyboard_state.m_xkb_state  = xkb_state;
}

void core::window::detail::WaylandImpl::wl_keyboard_leave(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface
) {
    core::log::trace("Keyboard Leave");
}

void core::window::detail::WaylandImpl::wl_keyboard_modifiers(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     mods_depressed,
    [[maybe_unused]] uint32_t     mods_latched,
    [[maybe_unused]] uint32_t     mods_locked,
    [[maybe_unused]] uint32_t     group
) {
    WaylandImpl* this_impl = static_cast<WaylandImpl*>(data);
    xkb_state_update_mask(
        this_impl->m_keyboard_state.m_xkb_state,
        mods_depressed,
        mods_latched,
        mods_locked,
        0,
        0,
        group
    );
}

void core::window::detail::WaylandImpl::wl_keyboard_repeat_info(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] int32_t      rate,
    [[maybe_unused]] int32_t      delay
) {}
