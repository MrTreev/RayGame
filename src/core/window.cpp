#include "core/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/config.h"
#include "core/logger.h"
#include "core/types.h"

#if defined(RAYGAME_GUI_WAYLAND)
#    include <wayland-client.h>
#endif

namespace {

#if defined(RAYGAME_GUI_WAYLAND)
struct {
    struct wl_display*  display  = nullptr;
    struct wl_registry* registry = nullptr;
} win_state;
#endif

} // namespace

core::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name,
    const WindowStyle& style
) {
#if defined(RAYGAME_GUI_WAYLAND)
    condition::pre_condition(
        win_state.display == nullptr,
        "Wayland display already created, cannot create another"
    );
    condition::pre_condition(
        win_state.registry == nullptr,
        "Wayland registry already created, cannot create another"
    );
    win_state.display  = wl_display_connect(nullptr);
    win_state.registry = wl_display_get_registry(win_state.display);
#endif
    log::debug("Window created");
}

core::Window::~Window() {
    log::debug("Window closing");
#if defined(RAYGAME_GUI_WAYLAND)
    wl_display_disconnect(win_state.display);
#endif
}

bool core::Window::should_close() {
    return false;
}
