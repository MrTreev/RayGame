#pragma once
#include "raygame/core/window/detail/wayland/display.h"
#include "raygame/core/window/detail/wayland/keyboard.h"
#include "raygame/core/window/detail/wayland/pointers.h"
#include "raygame/core/window/detail/wayland/registry.h"
#include "raygame/core/window/detail/wayland/seat.h"
#include "raygame/core/window/detail/wayland/surface.h"
#include "raygame/core/window/detail/wayland/xdg_base.h"
#include "raygame/core/window/detail/wayland/xdg_toplevel.h"
#include "raygame/core/window/window.h"
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include <xdg-shell-client-protocol.h>
#include <xkbcommon/xkbcommon.h>

namespace core::window::detail {
class WaylandWindowImpl final: public WindowImpl {
public:
    explicit WaylandWindowImpl(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    WaylandWindowImpl(const WaylandWindowImpl&)           = delete;
    WaylandWindowImpl operator=(const WaylandWindowImpl&) = delete;
    WaylandWindowImpl(WaylandWindowImpl&&)                = default;
    WaylandWindowImpl& operator=(WaylandWindowImpl&&)     = default;
    ~WaylandWindowImpl() final;

    void draw(const drawing::Image& image) final;

    void restyle(WindowStyle style) final;

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;

private:
    friend WaylandRegistry;
    WaylandDisplay     m_display;
    WaylandXdgToplevel m_toplevel;
    WaylandSurface     m_surface;
    WaylandXdgBase     m_base;
    WaylandSeat        m_seat;
};
} // namespace core::window::detail
