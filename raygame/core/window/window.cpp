#include "raygame/core/window/window.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/logger.h"
#include "raygame/core/window/detail/cocoa.h"
#include "raygame/core/window/detail/dwm.h"
#include "raygame/core/window/detail/imgui.h"
#include "raygame/core/window/detail/wayland.h"
#include "raygame/core/window/detail/x11.h"

namespace {

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
    using core::config::GuiBackend;
    using core::config::OperatingSystem;
    if constexpr (core::config::EnabledBackends::imgui()) {
        return GuiBackend::IMGUI;
    }
    switch (core::config::OPERATING_SYSTEM) {
    case OperatingSystem::ANDROID: unimplemented();
    case OperatingSystem::BSD:     [[fallthrough]];
    case OperatingSystem::HURD:    [[fallthrough]];
    case OperatingSystem::LINUX:   return wayland_or_x11();
    case OperatingSystem::MAC:     return GuiBackend::COCOA;
    case OperatingSystem::QNX:     unimplemented();
    case OperatingSystem::WIN32:   [[fallthrough]];
    case OperatingSystem::WIN64:   return GuiBackend::DWM;
    }
}
} // namespace

core::window::Window::Window(Vec2<size_t> size, std::string title, WindowStyle style) {
    const auto backend = get_backend();
    if constexpr (config::EnabledBackends::imgui()) {
        using Imgui = detail::ImguiWindowImpl;
        if (backend == config::GuiBackend::IMGUI) {
            m_impl = std::make_unique<Imgui>(size, std::move(title), style);
            return;
        }
    }
    if constexpr (config::EnabledBackends::cocoa()) {
        using Cocoa = detail::CocoaWindowImpl;
        if (backend == config::GuiBackend::COCOA) {
            m_impl = std::make_unique<Cocoa>(size, std::move(title), style);
            return;
        }
    }
    if constexpr (config::EnabledBackends::dwm()) {
        using Dwm = detail::DwmWindowImpl;
        if (backend == config::GuiBackend::DWM) {
            m_impl = std::make_unique<Dwm>(size, std::move(title), style);
            return;
        }
    }
    if constexpr (config::EnabledBackends::wayland()) {
        using Wayland = detail::WaylandWindowImpl;
        if (backend == config::GuiBackend::WAYLAND) {
            m_impl = std::make_unique<Wayland>(size, std::move(title), style);
            return;
        }
    }
    if constexpr (config::EnabledBackends::x11()) {
        using X11 = detail::X11WindowImpl;
        if (backend == config::GuiBackend::X11) {
            m_impl = std::make_unique<X11>(size, std::move(title), style);
            return;
        }
    }
}

core::window::detail::WindowImpl::~WindowImpl() {
    core::log::debug("Destroying Window: {}", m_title);
};

void core::window::detail::WindowImpl::draw([[maybe_unused]] const drawing::ImageView& image) {
    condition::unreachable();
}

void core::window::detail::WindowImpl::restyle([[maybe_unused]] WindowStyle style) {
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
