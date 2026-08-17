#include "raygame/core/application/detail/dwm.hpp"
#include "raygame/core/application/application.hpp"
#include "raygame/core/application/detail/backends.hpp"
#include "raygame/core/condition.hpp"
#include "raygame/core/drawing/image.hpp"
#include "raygame/core/math/vector.hpp"
#include "raygame/core/types.hpp"
#include <string>
#include <utility>

RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wmissing-noreturn")

core::detail::DwmWindowImpl::DwmWindowImpl(Vec2<size_t> size, std::string title, WindowStyle style)
    : AppImpl(size, std::move(title), style) {
    condition::unreachable();
}

RAYGAME_CLANG_SUPPRESS_WARNING_POP

core::detail::DwmWindowImpl::~DwmWindowImpl() = default;

void core::detail::DwmWindowImpl::draw(
    [[maybe_unused]] const drawing::ImageView& image,
    [[maybe_unused]] const Vec2<pos_t>&        position
) {
    condition::unimplemented();
}

void core::detail::DwmWindowImpl::restyle([[maybe_unused]] WindowStyle style) {
    condition::unimplemented();
}

void core::detail::DwmWindowImpl::render_frame() {
    condition::unimplemented();
}

bool core::detail::DwmWindowImpl::next_frame() {
    condition::unimplemented();
}

bool core::detail::DwmWindowImpl::should_close() const {
    condition::unimplemented();
}
