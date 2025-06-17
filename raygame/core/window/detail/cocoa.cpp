#include "raygame/core/window/detail/cocoa.h"
#include "raygame/core/condition.h"
#include "raygame/core/window/detail/backends.h"

core::window::detail::CocoaWindowImpl::CocoaWindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style) {
    if constexpr (!config::EnabledBackends::cocoa()) {
        condition::unreachable();
    }
}

core::window::detail::CocoaWindowImpl::~CocoaWindowImpl() = default;

void core::window::detail::CocoaWindowImpl::draw(const drawing::ImageView& image) {
    std::ignore = image;
    condition::unimplemented();
}

void core::window::detail::CocoaWindowImpl::restyle(WindowStyle style) {
    std::ignore = style;
    condition::unimplemented();
}

void core::window::detail::CocoaWindowImpl::render_frame() {
    condition::unimplemented();
}

bool core::window::detail::CocoaWindowImpl::next_frame() {
    condition::unimplemented();
}

bool core::window::detail::CocoaWindowImpl::should_close() const {
    condition::unimplemented();
}
