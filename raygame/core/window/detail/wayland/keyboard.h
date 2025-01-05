#pragma once
#include "raygame/core/types.h"
#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>

namespace core::window::detail {
class WaylandKeyboard {
    static constexpr size_t BUF_SIZE      = 128;
    static constexpr int    ADD_VAL       = 8;
    wl_keyboard*            m_wl_keyboard = nullptr;
    xkb_state*              m_xkb_state   = nullptr;
    xkb_keymap*             m_xkb_keymap  = nullptr;
    xkb_context*            m_xkb_context = nullptr;

    static void enter(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     serial,
        wl_surface*  surface,
        wl_array*    keys
    );

    static void key( //
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     serial,
        uint32_t     time,
        uint32_t     key,
        uint32_t     state
    );

    static void keymap(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     format,
        int32_t      shm_fd,
        uint32_t     size
    );

    static void leave(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     serial,
        wl_surface*  surface
    );

    static void modifiers(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     serial,
        uint32_t     mods_depressed,
        uint32_t     mods_latched,
        uint32_t     mods_locked,
        uint32_t     group
    );

    static void repeat_info(
        void*        data,
        wl_keyboard* wl_keyboard,
        int32_t      rate,
        int32_t      delay
    );

public:
    static const wl_keyboard_listener m_listener;
};
} // namespace core::window::detail
