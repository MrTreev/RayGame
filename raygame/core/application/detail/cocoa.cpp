#include "raygame/core/application/detail/cocoa.h"
#include "raygame/core/application/detail/backends.h"
#include "raygame/core/condition.h"
#include "raygame/core/config.h"

RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wmissing-noreturn")

core::detail::CocoaWindowImpl::CocoaWindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : AppImpl(size, std::move(title), style) {
    condition::unimplemented();
}

RAYGAME_CLANG_SUPPRESS_WARNING_POP

core::detail::CocoaWindowImpl::~CocoaWindowImpl() = default;

void core::detail::CocoaWindowImpl::draw(const drawing::ImageView& image) {
    std::ignore = image;
    condition::unimplemented();
}

void core::detail::CocoaWindowImpl::restyle(WindowStyle style) {
    std::ignore = style;
    condition::unimplemented();
}

void core::detail::CocoaWindowImpl::render_frame() {
    condition::unimplemented();
}

bool core::detail::CocoaWindowImpl::next_frame() {
    condition::unimplemented();
}

bool core::detail::CocoaWindowImpl::should_close() const {
    condition::unimplemented();
}
