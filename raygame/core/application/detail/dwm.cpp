#include "raygame/core/application/detail/dwm.h"
#include "raygame/core/application/application.h"
#include "raygame/core/application/detail/backends.h"
#include "raygame/core/condition.h"
#include "raygame/core/drawing/image.h"
#include "raygame/core/math/vector.h"
#include "raygame/core/types.h"
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

void core::detail::DwmWindowImpl::draw([[maybe_unused]] const drawing::ImageView& image) {
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
