#include "raygame/core/window/window.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include "raygame/core/logger.h"
#include "raygame/core/window/detail/backends.h"
#include "raygame/core/window/detail/cocoa.h"
#include "raygame/core/window/detail/dwm.h"
#include "raygame/core/window/detail/wayland.h"

core::window::Window::Window(Vec2<size_t> size, std::string title, WindowStyle style) {
    using Cocoa   = detail::CocoaWindowImpl;
    using Dwm     = detail::DwmWindowImpl;
    using Wayland = detail::WaylandWindowImpl;
    switch (config::BACKEND) {
    case config::GuiBackend::COCOA:
        m_impl = std::make_unique<Cocoa>(size, std::move(title), style);
        return;
    case config::GuiBackend::DWM:
        m_impl = std::make_unique<Dwm>(size, std::move(title), style);
        return;
    case config::GuiBackend::WAYLAND:
        m_impl = std::make_unique<Wayland>(size, std::move(title), style);
        return;
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

RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wmissing-noreturn")

void core::window::detail::WindowImpl::set_close() {
    condition::unreachable();
}

RAYGAME_CLANG_SUPPRESS_WARNING_POP

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
