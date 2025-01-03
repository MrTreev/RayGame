#pragma once
#include "raygame/core/types.h"
struct wl_keyboard;
struct wl_array;
struct wl_surface;
struct wl_keyboard_listener;
struct xkb_context;
struct xkb_keymap;
struct xkb_state;

namespace core::window::detail::wayland {
class WaylandKeyboard {
    static void wl_keyboard_enter(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     serial,
        wl_surface*  surface,
        wl_array*    keys
    );
    static void wl_keyboard_key(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     serial,
        uint32_t     time,
        uint32_t     key,
        uint32_t     state
    );
    static void wl_keyboard_keymap(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     format,
        int32_t      fd, // NOLINT(*-identifier-length)
        uint32_t     size
    );
    static void wl_keyboard_leave(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     serial,
        wl_surface*  surface
    );
    static void wl_keyboard_modifiers(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     serial,
        uint32_t     mods_depressed,
        uint32_t     mods_latched,
        uint32_t     mods_locked,
        uint32_t     group
    );
    static void wl_keyboard_repeat_info(
        void*        data,
        wl_keyboard* wl_keyboard,
        int32_t      rate,
        int32_t      delay
    );

private:
    wl_keyboard* m_wl_keyboard = nullptr;
    xkb_state*   m_xkb_state   = nullptr;
    xkb_keymap*  m_xkb_keymap  = nullptr;
    xkb_context* m_xkb_context = nullptr;
};
} // namespace core::window::detail::wayland
