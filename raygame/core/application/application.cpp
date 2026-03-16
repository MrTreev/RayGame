#include "raygame/core/application/application.h" // IWYU pragma: keep
#include "raygame/core/application/detail/backends.h"
#include "raygame/core/application/detail/cocoa.h"
#include "raygame/core/application/detail/dwm.h"
#include "raygame/core/application/detail/wayland.h"
#include "raygame/core/condition.h"
#include "raygame/core/logger.h"
#include "raygame/core/math/vector.h"

core::Application::Application(Vec2<size_t> size, std::string title, WindowStyle style) {
    if constexpr (config::BACKEND == config::GuiBackend::COCOA) {
        m_impl = std::make_unique<detail::CocoaWindowImpl>(size, std::move(title), style);
    } else if constexpr (config::BACKEND == config::GuiBackend::DWM) {
        m_impl = std::make_unique<detail::DwmWindowImpl>(size, std::move(title), style);
    } else if constexpr (config::BACKEND == config::GuiBackend::WAYLAND) {
        m_impl = std::make_unique<detail::AppImplWayland>(size, std::move(title), style);
    }
}

core::detail::AppImpl::~AppImpl() {
    core::log::debug("Destroying Window: {}", m_title);
};

void core::detail::AppImpl::draw(
    [[maybe_unused]] const drawing::ImageView& image,
    [[maybe_unused]] const Vec2<pos_t>&        position
) {
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
