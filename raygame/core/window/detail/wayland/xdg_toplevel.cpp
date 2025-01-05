#include "raygame/core/window/detail/wayland/xdg_toplevel.h"

//NOLINTBEGIN(*-easily-swappable-parameters)

namespace core::window::detail {
const xdg_toplevel_listener WaylandXdgToplevel::m_listener{
    .configure        = configure,
    .close            = close,
    .configure_bounds = configure_bounds,
    .wm_capabilities  = wm_capabilities,
};

void WaylandXdgToplevel::configure(
    [[maybe_unused]] void*         data,
    [[maybe_unused]] xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t       width,
    [[maybe_unused]] int32_t       height,
    [[maybe_unused]] wl_array*     states
) {}

void WaylandXdgToplevel::close(
    void*                          data,
    [[maybe_unused]] xdg_toplevel* xdg_toplevel
) {
    auto* self           = static_cast<WaylandXdgToplevel*>(data);
    self->m_should_close = true;
}

void WaylandXdgToplevel::configure_bounds(
    [[maybe_unused]] void*         data,
    [[maybe_unused]] xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t       width,
    [[maybe_unused]] int32_t       height
) {}

void WaylandXdgToplevel::wm_capabilities(
    [[maybe_unused]] void*         data,
    [[maybe_unused]] xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] wl_array*     capabilities
) {}

} // namespace core::window::detail

//NOLINTEND(*-easily-swappable-parameters)
