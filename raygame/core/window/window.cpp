#include "raygame/core/window/window.h" // IWYU pragma: keep #include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/logger.h"
#include "raygame/core/window/detail/cocoa.h"
#include "raygame/core/window/detail/dwm.h"
#include "raygame/core/window/detail/temple.h"
#include "raygame/core/window/detail/wayland.h"
#include "raygame/core/window/detail/x11.h"

namespace {
using core::config::GuiBackend;
using core::config::OperatingSystem;

core::config::GuiBackend wayland_or_x11() {
    const std::string session_type{
        std::getenv("XDG_SESSION_TYPE") // NOLINT(concurrency-mt-unsafe)
    };
    if (session_type == "wayland") {
        return core::config::GuiBackend::WAYLAND;
    }
    if (session_type == "x11") {
        return core::config::GuiBackend::X11;
    }
    core::log::warning(
        "Could not find XDG_SESSION_TYPE environment variable, "
        "falling back to X11"
    );
    return core::config::GuiBackend::X11;
}

core::config::GuiBackend get_backend() {
    using core::condition::unimplemented;
    switch (core::config::OPERATING_SYSTEM) {
    case OperatingSystem::ANDROID:  unimplemented();
    case OperatingSystem::BSD:      [[fallthrough]];
    case OperatingSystem::HURD:     [[fallthrough]];
    case OperatingSystem::LINUX:    return wayland_or_x11();
    case OperatingSystem::MAC:      return GuiBackend::COCOA;
    case OperatingSystem::QNX:      unimplemented();
    case OperatingSystem::TEMPLEOS: return GuiBackend::TEMPLE;
    case OperatingSystem::WIN32:    [[fallthrough]];
    case OperatingSystem::WIN64:    return GuiBackend::DWM;
    }
}
} // namespace

core::window::Window::Window(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
) {
    using Coc = detail::CocoaWindowImpl;
    using Dwm = detail::DwmWindowImpl;
    using Way = detail::WaylandWindowImpl;
    using X11 = detail::X11WindowImpl;
    using Tpl = detail::TempleWindowImpl;
    switch (get_backend()) {
    case config::GuiBackend::COCOA:
        m_impl = std::make_unique<Coc>(size, std::move(title), style);
        break;
    case config::GuiBackend::DWM:
        m_impl = std::make_unique<Dwm>(size, std::move(title), style);
        break;
    case config::GuiBackend::WAYLAND:
        m_impl = std::make_unique<Way>(size, std::move(title), style);
        break;
    case config::GuiBackend::X11:
        m_impl = std::make_unique<X11>(size, std::move(title), style);
        break;
    case config::GuiBackend::TEMPLE:
        m_impl = std::make_unique<Tpl>(size, std::move(title), style);
        break;
    }
}

core::window::detail::WindowImpl::~WindowImpl() = default;

void core::window::detail::WindowImpl::draw(
    [[maybe_unused]] const drawing::Image& image
) {
    condition::unreachable();
}

void core::window::detail::WindowImpl::restyle(
    [[maybe_unused]] WindowStyle style
) {
    condition::unreachable();
}

void core::window::detail::WindowImpl::render_frame() {
    condition::unreachable();
}

bool core::window::detail::WindowImpl::next_frame() {
    condition::unreachable();
}

bool core::window::detail::WindowImpl::should_close() const {
    condition::unreachable();
}
