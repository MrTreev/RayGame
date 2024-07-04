#include "core/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/logger.h"
#include "core/math.h"
#include "core/types.h"
#include <wayland-client-core.h>
#if defined(RAYGAME_GUI_WAYLAND)
#    include "core/windowimpl/wayland.h"
using core::window::wayland::wayland_state;
#endif

namespace {
constexpr size_t COLOUR_CHANNELS = 4;
constexpr size_t N_BUFFERS       = 2;
using core::condition::check_condition;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;

} // namespace

core::Window::Window(
    const core::Vec2<decltype(m_height)>& size,
    std::string                           title,
    const WindowStyle&                    style
)
    : core::Window::Window(size.x, size.y, std::move(title), style) {}

core::Window::Window(
    const size_t&      width,
    const size_t&      height,
    std::string        title,
    const WindowStyle& style
)
    : m_title(std::move(title))
    , m_height(numeric_cast<decltype(m_height)>(height))
    , m_width(numeric_cast<decltype(m_width)>(width))
    , m_buffer_size(numeric_cast<decltype(m_buffer_size)>(width * height)) {
    log::debug("Constructing");
#if defined(RAYGAME_GUI_WAYLAND)
    wayland_state.m_display = wl_display_connect(nullptr);
    check_condition(wayland_state.m_display != nullptr, "Display setup failed");
    wayland_state.m_registry = wl_display_get_registry(wayland_state.m_display);
    check_condition(
        wayland_state.m_registry != nullptr,
        "Registry setup failed"
    );
    wl_registry_add_listener(
        wayland_state.m_registry,
        &registry_listener,
        nullptr
    );
    check_condition(
        wl_display_roundtrip(wayland_state.m_display) != 0,
        "Display roundtrip failed"
    );
    check_condition(
        wayland_state.m_shm != nullptr,
        "shm global not setup correctly"
    );
    check_condition(
        wayland_state.m_compositor != nullptr,
        "compositor global not setup correctly"
    );
    check_condition(
        wayland_state.m_xdg_wm_base != nullptr,
        "xdg_wm_base global not setup correctly"
    );
    wayland_state.m_surface =
        wl_compositor_create_surface(wayland_state.m_compositor);
    struct xdg_surface* xdg_surface = xdg_wm_base_get_xdg_surface(
        wayland_state.m_xdg_wm_base,
        wayland_state.m_surface
    );
    wayland_state.m_xdg_toplevel = xdg_surface_get_toplevel(xdg_surface);
    wl_surface_commit(wayland_state.m_surface);
    while (wl_display_dispatch(wayland_state.m_display) != -1
           && !wayland_state.m_configured) {}
    struct wl_buffer* buffer =
        core::window::wayland::create_buffer(m_width, m_height, m_buffer_size);
    check_condition(buffer != nullptr, "Failed to setup buffer");
#endif
    log::debug("Constructed");
}

core::Window::~Window() {
    log::debug("Destructing");
#if defined(RAYGAME_GUI_WAYLAND)

#endif
    log::debug("Destructed");
}

bool core::Window::should_close() { // NOLINT *-member-functions-to-static
#if defined(RAYGAME_GUI_WAYLAND)
    return core::window::wayland::wayland_state.m_running;
#else
    return false;
#endif
}

void core::Window::render() {}
