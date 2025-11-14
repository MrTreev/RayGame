#include "raygame/core/application.h" // IWYU pragma: keep
#include "raygame/core/application/detail/backends.h"
#include "raygame/core/application/detail/cocoa.h"
#include "raygame/core/application/detail/dwm.h"
#include "raygame/core/application/detail/wayland.h"
#include "raygame/core/condition.h"
#include "raygame/core/logger.h"

core::Application::Application(Vec2<size_t> size, std::string title, WindowStyle style) {
    using Cocoa   = detail::CocoaWindowImpl;
    using Dwm     = detail::DwmWindowImpl;
    using Wayland = detail::AppImplWayland;
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

core::detail::AppImpl::~AppImpl() {
    core::log::debug("Destroying Window: {}", m_title);
};

void core::detail::AppImpl::draw([[maybe_unused]] const drawing::ImageView& image) {
    condition::unreachable();
}

void core::detail::AppImpl::restyle([[maybe_unused]] WindowStyle style) {
    condition::unreachable();
}

void core::detail::AppImpl::render_frame() {
    condition::unreachable();
}

bool core::detail::AppImpl::next_frame() {
    condition::unreachable();
}

bool core::detail::AppImpl::should_close() const {
    condition::unreachable();
}

RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wmissing-noreturn")

void core::detail::AppImpl::set_close() {
    condition::unreachable();
}

RAYGAME_CLANG_SUPPRESS_WARNING_POP

std::string core::detail::AppImpl::frame_stats() {
    return std::format(
        "Min Frame Time: {}\n"
        "Max Frame Time: {}\n"
        "Ave Frame Time: {}",
        m_counter.min(),
        m_counter.max(),
        m_counter.average()
    );
}
