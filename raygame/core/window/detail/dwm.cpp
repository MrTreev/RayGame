#include "raygame/core/window/detail/dwm.h"
#include "raygame/core/condition.h"
#include "raygame/core/window/detail/backends.h"

RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wmissing-noreturn")

core::window::detail::DwmWindowImpl::DwmWindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style) {
    condition::unreachable();
}

RAYGAME_CLANG_SUPPRESS_WARNING_POP

core::window::detail::DwmWindowImpl::~DwmWindowImpl() = default;

void core::window::detail::DwmWindowImpl::draw(const drawing::ImageView& image) {
    std::ignore = image;
    condition::unimplemented();
}

void core::window::detail::DwmWindowImpl::restyle(WindowStyle style) {
    std::ignore = style;
    condition::unimplemented();
}

void core::window::detail::DwmWindowImpl::render_frame() {
    condition::unimplemented();
}

bool core::window::detail::DwmWindowImpl::next_frame() {
    condition::unimplemented();
}

bool core::window::detail::DwmWindowImpl::should_close() const {
    condition::unimplemented();
}
