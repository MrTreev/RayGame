#include "raygame/core/window/window.h" // IWYU pragma: keep
#include "raygame/core/logger.h"
#include "raygame/core/window/wayland.h"
#include "raygame/core/window/x11.h"

core::window::Window::~Window() = default;
void core::window::Window::render_frame(){ log::error("base"); }
std::unique_ptr<core::window::Window> core::window::dispatch(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
) {
    if constexpr (config::WindowBackend::wayland_enabled()) {
        return std::make_unique<WaylandWindow>(size, std::move(title), style);
    }
    if constexpr (config::WindowBackend::x11_enabled()) {
        return std::make_unique<X11Window>(size, std::move(title), style);
    }
    if constexpr (config::WindowBackend::dwm_enabled()) {
        condition::unimplemented();
    }
    if constexpr (config::WindowBackend::cocoa_enabled()) {
        condition::unimplemented();
    }
}
