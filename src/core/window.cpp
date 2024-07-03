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

#endif
    log::debug("Constructed");
}

core::Window::~Window() {
    log::debug("Destructing");
#if defined(RAYGAME_GUI_WAYLAND)

#endif
    log::debug("Destructed");
}

bool core::Window::should_close() {
    pre_condition(true, "Cannot check if null window should close");
    const bool close_now = false;
    log::debug(close_now ? "True" : "False");
    return close_now;
}

void core::Window::render() {}
