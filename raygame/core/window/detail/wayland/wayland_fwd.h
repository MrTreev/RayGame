#pragma once
#include "raygame/core/window/detail/backends.h" // IWYU pragma: keep
// Using the C header here, to guarantee the global-namespace types
#if !defined(RAYGAME_GUI_BACKEND_WAYLAND)
#    include <wayland-client-protocol.h>   // IWYU pragma: export
#    include <xdg-shell-client-protocol.h> // IWYU pragma: export
#    include <xkbcommon/xkbcommon.h>       // IWYU pragma: export
#else
extern "C" {
#    include <stdint.h> // NOLINT(*-deprecated-headers)

    struct wl_array;
    using wl_fixed_t = int32_t;
    struct xkb_state;
    struct xkb_keymap;
    struct xkb_context;
    struct wl_buffer;
    struct wl_callback;
    struct wl_compositor;
    struct wl_display;
    struct wl_keyboard;
    struct wl_pointer;
    struct wl_registry;
    struct wl_seat;
    struct wl_shm;
    struct wl_shm_pool;
    struct wl_surface;
    struct xdg_surface;
    struct xdg_toplevel;
    struct xdg_wm_base;

    struct wl_callback_listener;
    struct wl_keyboard_listener;
    struct wl_pointer_listener;
    struct wl_registry_listener;
    struct wl_seat_listener;
    struct xdg_surface_listener;
    struct xdg_toplevel_listener;
    struct xdg_wm_base_listener;

    void xkb_state_unref(struct xkb_state* state);
    void xkb_keymap_unref(struct xkb_keymap* keymap);
    void xkb_context_unref(struct xkb_context* context);

    enum xkb_context_flags { // NOLINT(*-enum-size)
        XKB_CONTEXT_NO_FLAGS             = 0,
        XKB_CONTEXT_NO_DEFAULT_INCLUDES  = (1U << 0U),
        XKB_CONTEXT_NO_ENVIRONMENT_NAMES = (1U << 1U),
        XKB_CONTEXT_NO_SECURE_GETENV     = (1U << 2U)
    };

    struct xkb_context* xkb_context_new(xkb_context_flags flags);
}
#endif
