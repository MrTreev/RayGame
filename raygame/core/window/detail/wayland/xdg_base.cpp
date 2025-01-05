#include "raygame/core/window/detail/wayland/xdg_base.h"

namespace core::window::detail {
const xdg_wm_base_listener WaylandXdgBase::m_listener{
    .ping = ping,
};

void WaylandXdgBase::ping(
    [[maybe_unused]] void* data,
    xdg_wm_base*           xdg_wm_base,
    uint32_t               serial
) {
    xdg_wm_base_pong(xdg_wm_base, serial);
}
} // namespace core::window::detail
