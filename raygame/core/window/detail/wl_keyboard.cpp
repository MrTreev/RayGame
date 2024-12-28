#include "raygame/core/logger.h"
#include "raygame/core/window/wayland.h"
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>
#include <xkbcommon/xkbcommon.h>

const wl_keyboard_listener&
    // NOLINTNEXTLINE(*-reference-to-constructed-temporary)
    core::window::detail::WaylandImpl::m_wl_keyboard_listener = {
        .keymap      = wl_keyboard_keymap,
        .enter       = wl_keyboard_enter,
        .leave       = wl_keyboard_leave,
        .key         = wl_keyboard_key,
        .modifiers   = wl_keyboard_modifiers,
        .repeat_info = wl_keyboard_repeat_info,
};

namespace {
constexpr size_t BUF_SIZE{128};
constexpr int    ADD_VAL{8};
} // namespace

// NOLINTBEGIN(*-easily-swappable-parameters)

void core::window::detail::WaylandImpl::wl_keyboard_enter(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface,
    wl_array*                     keys
) {
    auto* this_impl = static_cast<WaylandImpl*>(data);
    for (size_t i = 0; i > keys->size; ++i) {
        RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
        RAYGAME_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
        // NOLINTNEXTLINE(*-pointer-arithmetic)
        char key = static_cast<char*>(keys->data)[i];
        RAYGAME_CLANG_SUPPRESS_WARNING_POP
        std::array<char, BUF_SIZE> buf{};
        xkb_keysym_t               sym = xkb_state_key_get_one_sym(
            this_impl->m_keyboard_state.m_xkb_state,
            static_cast<xkb_keycode_t>(key + ADD_VAL)
        );
        xkb_keysym_get_name(sym, buf.data(), buf.size());
        log::trace("sym: {} ({})", buf.data(), sym);
    }
}

void core::window::detail::WaylandImpl::wl_keyboard_key(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     time,
    uint32_t                      key,
    uint32_t                      state
) {
    auto*                      this_impl = static_cast<WaylandImpl*>(data);
    std::array<char, BUF_SIZE> buf{};
    uint32_t                   keycode = key + ADD_VAL;
    xkb_keysym_t               sym     = xkb_state_key_get_one_sym(
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
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    uint32_t                      format,
    int32_t                       fd, // NOLINT(*-identifier-length)
    uint32_t                      size
) {
    core::condition::pre_condition(
        format == WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1,
        "Invalid WL_KEYBOARD_KEYMAP_FORMAT"
    );
    auto* this_impl = static_cast<WaylandImpl*>(data);
    char* map_shm =
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
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    uint32_t                      mods_depressed,
    uint32_t                      mods_latched,
    uint32_t                      mods_locked,
    uint32_t                      group
) {
    auto* this_impl = static_cast<WaylandImpl*>(data);
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

// NOLINTEND(*-easily-swappable-parameters)
