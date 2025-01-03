#include "raygame/core/window/detail/x11.h"
#include "raygame/core/condition.h"
#if defined(RAYGAME_GUI_BACKEND_X11)
RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
#    include <X11/Xlib.h>
RAYGAME_CLANG_SUPPRESS_WARNING_POP
#endif

core::window::detail::X11WindowImpl::X11WindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style) {}

core::window::detail::X11WindowImpl::~X11WindowImpl() = default;

void core::window::detail::X11WindowImpl::draw(const drawing::Image& image) {
    std::ignore = image;
    condition::unimplemented();
}

void core::window::detail::X11WindowImpl::restyle(WindowStyle style) {
    std::ignore = style;
    condition::unimplemented();
}

void core::window::detail::X11WindowImpl::render_frame() {
    condition::unimplemented();
}

bool core::window::detail::X11WindowImpl::next_frame() {
    condition::unimplemented();
}

bool core::window::detail::X11WindowImpl::should_close() const {
    condition::unimplemented();
}
