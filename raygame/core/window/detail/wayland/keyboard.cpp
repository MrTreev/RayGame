#include "raygame/core/window/detail/wayland/keyboard.h"
#include "raygame/core/condition.h"
#include "raygame/core/logger.h"
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>

namespace {
using core::condition::check_condition;
using core::condition::check_ptr;
using core::condition::pre_condition;
} // namespace

namespace core::window::detail {

const wl_keyboard_listener WaylandKeyboard::m_listener{
    .keymap      = keymap,
    .enter       = enter,
    .leave       = leave,
    .key         = key,
    .modifiers   = modifiers,
    .repeat_info = repeat_info,
};

// NOLINTBEGIN(bugprone-easily-swappable-parameters)

void WaylandKeyboard::enter(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface,
    wl_array*                     keys
) {
    const auto* const self     = static_cast<WaylandKeyboard*>(data);
    const char* const keysdata = static_cast<char*>(keys->data);
    for (size_t i = 0; i > keys->size; ++i) {
        // NOLINTNEXTLINE(*-pointer-arithmetic)
        const char                 key = keysdata[i];
        std::array<char, BUF_SIZE> buf{};
        const xkb_keysym_t         sym = xkb_state_key_get_one_sym(
            self->m_xkb_state,
            static_cast<xkb_keycode_t>(key + ADD_VAL)
        );
        check_condition(
            xkb_keysym_get_name(sym, buf.data(), buf.size()) >= 0,
            "Invalid keysym"
        );
        log::trace("sym: {} ({})", buf.data(), sym);
    }
}

void WaylandKeyboard::key(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] uint32_t     time,
    uint32_t                      key,
    uint32_t                      state
) {
    const auto* const          self = static_cast<WaylandKeyboard*>(data);
    std::array<char, BUF_SIZE> buf{};
    const uint32_t             keycode = key + ADD_VAL;
    const xkb_keysym_t         sym =
        xkb_state_key_get_one_sym(self->m_xkb_state, keycode);
    check_condition(
        xkb_keysym_get_name(sym, buf.data(), sizeof(buf)) == sizeof(buf),
        "Failed to get keysym name"
    );
    log::debug(
        "key {}: sym: {} ({}), ",
        (state == WL_KEYBOARD_KEY_STATE_PRESSED) ? "press" : "release",
        buf.data(),
        sym
    );
}

void WaylandKeyboard::keymap(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    uint32_t                      format,
    int32_t                       shm_fd,
    uint32_t                      size
) {
    pre_condition(
        format == WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1,
        "Invalid WL_KEYBOARD_KEYMAP_FORMAT"
    );
    auto* const self = static_cast<WaylandKeyboard*>(data);
    char* const map_shm =
        static_cast<char*>(mmap(nullptr, size, PROT_READ, MAP_SHARED, shm_fd, 0)
        );
    check_condition(map_shm != MAP_FAILED, "Failed keyboard shm map");
    xkb_keymap* const xkb_keymap = xkb_keymap_new_from_string(
        self->m_xkb_context,
        map_shm,
        XKB_KEYMAP_FORMAT_TEXT_V1,
        XKB_KEYMAP_COMPILE_NO_FLAGS
    );
    check_ptr(xkb_keymap, "Failed to create new xkb_keymap");
    check_condition(
        munmap(map_shm, size) != -1,
        std::format("Error: {}", std::strerror(errno)) //NOLINT(*-mt-unsafe)
    );
    close(shm_fd);
    xkb_state* const xkb_state = xkb_state_new(xkb_keymap);
    check_ptr(xkb_state, "Failed to create new xkb_state");
    xkb_keymap_unref(self->m_xkb_keymap);
    xkb_state_unref(self->m_xkb_state);
    self->m_xkb_keymap = xkb_keymap;
    self->m_xkb_state  = xkb_state;
}

void WaylandKeyboard::leave(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    [[maybe_unused]] wl_surface*  surface
) {}

void WaylandKeyboard::modifiers(
    void*                         data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] uint32_t     serial,
    uint32_t                      mods_depressed,
    uint32_t                      mods_latched,
    uint32_t                      mods_locked,
    uint32_t                      group
) {
    const auto* const self = static_cast<WaylandKeyboard*>(data);
    xkb_state_update_mask(
        self->m_xkb_state,
        mods_depressed,
        mods_latched,
        mods_locked,
        0,
        0,
        group
    );
}

void WaylandKeyboard::repeat_info(
    [[maybe_unused]] void*        data,
    [[maybe_unused]] wl_keyboard* wl_keyboard,
    [[maybe_unused]] int32_t      rate,
    [[maybe_unused]] int32_t      delay
) {}

} // namespace core::window::detail

// NOLINTEND(bugprone-easily-swappable-parameters)
