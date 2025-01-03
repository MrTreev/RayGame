#pragma once
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
    uint32_t m_shm_format;
};
} // namespace core::window::detail
