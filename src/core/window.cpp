#include "core/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/logger.h"
#include "core/math.h"
#include "core/types.h"
#if defined(RAYGAME_GUI_WAYLAND)
#    include "core/windowimpl/wayland.h"
using core::WaylandWinState;
#endif

namespace {
constexpr size_t COLOUR_CHANNELS = 4;
constexpr size_t N_BUFFERS       = 2;
using core::condition::check_condition;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;

const struct wl_registry_listener registry_listener = {
    .global        = core::window::impl::wayland::registry_handle_global,
    .global_remove = core::window::impl::wayland::registry_handle_global_remove,
};

const struct wl_buffer_listener buffer_listener = {
    .release = core::window::impl::wayland::buffer_release,
};
const struct wl_surface_listener surface_listener = {
    .enter = core::window::impl::wayland::surface_enter_handler,
    .leave = core::window::impl::wayland::surface_leave_handler
};
const struct zxdg_surface_v6_listener xdg_surface_listener = {
    .configure = core::window::impl::wayland::xdg_surface_configure,
};

const struct zxdg_toplevel_v6_listener xdg_toplevel_listener = {
    .configure = core::window::impl::wayland::xdg_toplevel_configure_handler,
    .close     = core::window::impl::wayland::xdg_toplevel_close_handler
};

} // namespace

core::Window::Window(
    const core::Vec2<size_t>& size,
    const std::string&        title,
    const WindowStyle&        style
)
    : core::Window::Window(size.x, size.y, title, style) {}

core::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& title,
    const WindowStyle& style
)
    : m_win_state(std::make_unique<core::WaylandWinState>()) {
    log::debug("Constructing");
    m_win_state->m_title       = title;
    m_win_state->m_height      = height;
    m_win_state->m_width       = width;
    m_win_state->m_buffer_size = width * height;
#if defined(RAYGAME_GUI_WAYLAND)

    m_win_state->m_display = wl_display_connect(nullptr);
    check_condition(
        m_win_state->m_display != nullptr,
        "Unable to create Wayland display"
    );

    m_win_state->m_registry = wl_display_get_registry(m_win_state->m_display);
    check_condition(
        m_win_state->m_registry != nullptr,
        "Unable to create Wayland registry"
    );

    wl_registry_add_listener(
        m_win_state->m_registry,
        &registry_listener,
        m_win_state.get()
    );
    wl_display_roundtrip(m_win_state->m_display);
    m_win_state->m_surface =
        wl_compositor_create_surface(m_win_state->m_compositor);
    check_condition(
        m_win_state->m_surface != nullptr,
        "Unable to create Wayland Surface"
    );
    wl_surface_add_listener(m_win_state->m_surface, &surface_listener, nullptr);
    log::debug("Surface");
    m_win_state->m_shm_fd =
        numeric_cast<int>(syscall(SYS_memfd_create, "buffer", 0));
    ftruncate(
        m_win_state->m_shm_fd,
        numeric_cast<__off_t>(m_win_state->m_buffer_size * COLOUR_CHANNELS)
    );
    auto* data = static_cast<uint8_t*>(mmap(
        nullptr,
        m_win_state->m_buffer_size * COLOUR_CHANNELS,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        m_win_state->m_shm_fd,
        0
    ));

    log::debug("Truncated");
    m_win_state->m_xdg_surface = zxdg_shell_v6_get_xdg_surface(
        m_win_state->m_shell,
        m_win_state->m_surface
    );
    zxdg_surface_v6_add_listener(
        m_win_state->m_xdg_surface,
        &xdg_surface_listener,
        nullptr
    );
    m_win_state->m_xdg_toplevel =
        zxdg_surface_v6_get_toplevel(m_win_state->m_xdg_surface);
    zxdg_toplevel_v6_add_listener(
        m_win_state->m_xdg_toplevel,
        &xdg_toplevel_listener,
        nullptr
    );
    m_win_state->m_pool = wl_shm_create_pool(
        m_win_state->m_shm,
        m_win_state->m_shm_fd,
        numeric_cast<int32_t>(m_win_state->m_buffer_size)
    );
    m_win_state->m_buffer = wl_shm_pool_create_buffer(
        m_win_state->m_pool,
        0,
        numeric_cast<int32_t>(width),
        numeric_cast<int32_t>(height),
        numeric_cast<int32_t>(width * COLOUR_CHANNELS),
        WL_SHM_FORMAT_XRGB8888
    );
    wl_surface_attach(m_win_state->m_surface, m_win_state->m_buffer, 0, 0);
    wl_surface_commit(m_win_state->m_surface);

#endif
    log::debug("Constructed");
}

core::Window::~Window() {
    log::debug("Destructing");
#if defined(RAYGAME_GUI_WAYLAND)
    wl_display_disconnect(m_win_state->m_display);
#endif
    log::debug("Destructed");
}

bool core::Window::should_close() {
    pre_condition(
        m_win_state->m_display != nullptr,
        "Cannot check if null window should close"
    );
    const bool close_now = false;
    log::debug(close_now ? "True" : "False");
    return close_now;
}

void core::Window::render() {
    wl_display_dispatch(m_win_state->m_display);
}
