#include "core/window.h"
#include "core/condition.h"
#include "core/logger.h"
#include "core/math.h"
#include "core/types.h"

#if defined(RAYGAME_GUI_WAYLAND)
#    include "core/windowimpl/wayland.h"
#endif

namespace {
using core::math::numeric_cast;
} // namespace

core::Window::Window(
    const core::Vec2<decltype(m_height)>& size,
    std::string                           title,
    const WindowStyle&                    style
)
    : core::Window::Window(size.x, size.y, std::move(title), style) {}

core::Window::Window(
    const size_t&                       width,
    const size_t&                       height,
    std::string                         title,
    [[maybe_unused]] const WindowStyle& style
)
    : m_title(std::move(title))
    , m_width(numeric_cast<decltype(m_width)>(width))
    , m_height(numeric_cast<decltype(m_height)>(height))
    , m_buffer_size(numeric_cast<decltype(m_buffer_size)>(width * height)) {
    log::debug("Constructing");
#if defined(RAYGAME_GUI_WAYLAND)
    core::window::wayland::init_window(
        m_width,
        m_height,
        m_buffer_size,
        m_title,
        style
    );
#endif
    log::debug("Constructed");
}

core::Window::~Window() {
    log::debug("Destructing");
#if defined(RAYGAME_GUI_WAYLAND)
    core::window::wayland::destroy_window();
#endif
    log::debug("Destructed");
}

bool core::Window::should_close() {
#if defined(RAYGAME_GUI_WAYLAND)
    return core::window::wayland::should_close();
#else
    return true;
#endif
}

void core::Window::render() const {
    condition::pre_condition(!should_close(), "Window should close");
#if defined(RAYGAME_GUI_WAYLAND)
    core::window::wayland::render_frame(m_width, m_height);
#endif
}
