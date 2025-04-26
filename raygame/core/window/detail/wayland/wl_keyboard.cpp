#include "raygame/core/window/detail/wayland.h"
#if defined(RAYGAME_GUI_BACKEND_WAYLAND)
#    include <sys/mman.h>
#    include <unistd.h>
#    include <wayland-client-protocol.h>
#    include <xkbcommon/xkbcommon.h>

const wl_keyboard_listener
    core::window::detail::WaylandWindowImpl::m_wl_keyboard_listener = {
        .keymap      = wl_keyboard_keymap,
        .enter       = wl_keyboard_enter,
        .leave       = wl_keyboard_leave,
        .key         = wl_keyboard_key,
        .modifiers   = wl_keyboard_modifiers,
        .repeat_info = wl_keyboard_repeat_info,
};

// NOLINTBEGIN(*-easily-swappable-parameters)

void core::window::detail::WaylandWindowImpl::wl_keyboard_enter(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface,
    [[maybe_unused]] wl_array*    keys
) {}

void core::window::detail::WaylandWindowImpl::wl_keyboard_key(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     time,
    uint32_t                      key,
    uint32_t                      state
) {
    auto& keystate = static_cast<WaylandWindowImpl*>(data)->m_keyboard_state;
    keystate.event(key, state);
}

void core::window::detail::WaylandWindowImpl::wl_keyboard_keymap(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    uint32_t                      format,
    int32_t                       shm_fd,
    uint32_t                      size
) {
    core::condition::pre_condition(
        format == WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1,
        "Invalid WL_KEYBOARD_KEYMAP_FORMAT"
    );
    char* map_shm = static_cast<char*>(
        mmap(nullptr, size, PROT_READ, MAP_PRIVATE, shm_fd, 0)
    );
    core::condition::check_condition(
        map_shm != MAP_FAILED,
        "Failed keyboard shm map"
    );
    auto& keystate = static_cast<WaylandWindowImpl*>(data)->m_keyboard_state;
    keystate.new_from_string(map_shm);
    munmap(map_shm, size);
    close(shm_fd);
}

void core::window::detail::WaylandWindowImpl::wl_keyboard_leave(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface
) {}

void core::window::detail::WaylandWindowImpl::wl_keyboard_modifiers(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    uint32_t                      mods_depressed,
    uint32_t                      mods_latched,
    uint32_t                      mods_locked,
    uint32_t                      group
) {
    auto& keystate = static_cast<WaylandWindowImpl*>(data)->m_keyboard_state;
    keystate.update_mask(mods_depressed, mods_latched, mods_locked, group);
}

void core::window::detail::WaylandWindowImpl::wl_keyboard_repeat_info(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    int32_t                       rate,
    int32_t                       delay
) {
    auto& keystate = static_cast<WaylandWindowImpl*>(data)->m_keyboard_state;
    keystate.set_rate(rate);
    keystate.set_delay(delay);
}

// NOLINTEND(*-easily-swappable-parameters)
#endif
