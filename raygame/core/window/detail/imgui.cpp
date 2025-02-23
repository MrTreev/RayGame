#include "raygame/core/window/detail/imgui.h"

namespace core::window::detail {
namespace {
using core::condition::unimplemented;
using core::condition::unreachable;
} // namespace

ImguiWindowImpl::ImguiWindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style) {
    if constexpr (config::EnabledBackends::imgui()) {
    } else {
        unreachable();
    }
}
