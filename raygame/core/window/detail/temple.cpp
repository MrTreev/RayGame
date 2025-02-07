#include "raygame/core/window/detail/temple.h"

#if defined(RAYGAME_GUI_BACKEND_TEMPLE)
#    include "raygame/core/condition.h"

core::window::detail::TempleWindowImpl::TempleWindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style) {}

core::window::detail::TempleWindowImpl::~TempleWindowImpl() = default;

void core::window::detail::TempleWindowImpl::draw(
    const drawing::ImageView& image
) {
    std::ignore = image;
    core::condition::unimplemented();
}

void core::window::detail::TempleWindowImpl::restyle(WindowStyle style) {
    std::ignore = style;
    core::condition::unimplemented();
}

void core::window::detail::TempleWindowImpl::render_frame() {
    core::condition::unimplemented();
}

bool core::window::detail::TempleWindowImpl::next_frame() {
    core::condition::unimplemented();
}

bool core::window::detail::TempleWindowImpl::should_close() const {
    core::condition::unimplemented();
}
#endif
