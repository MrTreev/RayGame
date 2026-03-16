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

void core::detail::CocoaWindowImpl::draw(
    [[maybe_unused]] const drawing::ImageView& image,
    [[maybe_unused]] const Vec2<pos_t>&        position
) {
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
