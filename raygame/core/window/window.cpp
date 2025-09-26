#include "raygame/core/window/window.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/logger.h"
#include "raygame/core/window/detail/backends.h"
#include "raygame/core/window/detail/cocoa.h"
#include "raygame/core/window/detail/dwm.h"
#include "raygame/core/window/detail/raylib.h"
#include "raygame/core/window/detail/wayland.h"

namespace {

core::config::GuiBackend get_backend() {
    using core::condition::unimplemented;
    using core::config::GuiBackend;
    using core::config::OperatingSystem;
    // if constexpr (core::config::EnabledBackends::raylib()) {
    //     return GuiBackend::RAYLIB;
    // }
    switch (core::config::OPERATING_SYSTEM) {
    case OperatingSystem::ANDROID: unimplemented();
    case OperatingSystem::BSD:     [[fallthrough]];
    case OperatingSystem::LINUX:   return GuiBackend::WAYLAND;
    case OperatingSystem::MAC:     return GuiBackend::COCOA;
    case OperatingSystem::WIN64:   return GuiBackend::DWM;
    }
}
} // namespace

core::window::Window::Window(Vec2<size_t> size, std::string title, WindowStyle style) {
    const auto backend = get_backend();
    if constexpr (config::EnabledBackends::raylib()) {
        using Raylib = detail::RaylibWindowImpl;
        if (backend == config::GuiBackend::RAYLIB) {
            m_impl = std::make_unique<Raylib>(size, std::move(title), style);
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

std::string core::window::detail::WindowImpl::frame_stats() {
    return std::format(
        "Min Frame Time: {}\n"
        "Max Frame Time: {}\n"
        "Ave Frame Time: {}",
        m_counter.min(),
        m_counter.max(),
        m_counter.average()
    );
}
