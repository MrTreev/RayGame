#include "core/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/config.h"
#include "core/logger.h"
#include "core/types.h"
#include <memory>

#if defined(RAYGAME_GUI_WAYLAND)
#    include <wayland-client-protocol.h>
#    include <wayland-client.h>
#endif

#if defined(RAYGAME_GUI_WAYLAND)
struct core::WaylandWinState {
    struct wl_display*    display    = nullptr;
    struct wl_registry*   registry   = nullptr;
    struct wl_compositor* compositor = nullptr;
    struct wl_surface*    surface    = nullptr;
};

void registry_handle_global(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name,
    const char*         interface,
    uint32_t            version
) {
    core::log::debug(std::format(
        "interface: '{}', version: '{}', name: '{}'",
        interface,
        version,
        name
    ));
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        _win_state->compositor =
            wl_registry_bind(registry, name, &wl_compositor_interface, 4);
    }
}

void registry_handle_global_remove(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name
) {
    // Left Blank
}

const struct wl_registry_listener registry_listener = {
    .global        = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};

#endif

core::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name,
    const WindowStyle& style
)
    : _win_state(std::make_unique<core::WaylandWinState>()) {
    log::debug("Window attempt");
#if defined(RAYGAME_GUI_WAYLAND)
    _win_state->display  = wl_display_connect(nullptr);
    _win_state->registry = wl_display_get_registry(_win_state->display);
    wl_registry_add_listener(_win_state->registry, &registry_listener, nullptr);
    wl_display_roundtrip(_win_state->display);
#endif
    log::debug("Window created");
}

core::Window::~Window() {
    log::debug("Window closing");
#if defined(RAYGAME_GUI_WAYLAND)
    wl_display_disconnect(_win_state->display);
#endif
}

bool core::Window::should_close() {
    return (wl_display_dispatch(_win_state->display) != -1);
}
