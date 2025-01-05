#pragma once
#include "raygame/core/types.h"
#include <xdg-shell-client-protocol.h>

namespace core::window::detail {
class WaylandXdgToplevel {
    bool m_should_close{false};

    static void configure(
        void*         data,
        xdg_toplevel* xdg_toplevel,
        int32_t       width,
        int32_t       height,
        wl_array*     states
    );

    static void close(void* data, xdg_toplevel* xdg_toplevel);

    static void configure_bounds(
        void*         data,
        xdg_toplevel* xdg_toplevel,
        int32_t       width,
        int32_t       height
    );

    static void wm_capabilities(
        void*         data,
        xdg_toplevel* xdg_toplevel,
        wl_array*     capabilities
    );

public:
    WaylandXdgToplevel();
    ~WaylandXdgToplevel();
    WaylandXdgToplevel(const WaylandXdgToplevel&)            = delete;
    WaylandXdgToplevel(WaylandXdgToplevel&&)                 = default;
    WaylandXdgToplevel& operator=(const WaylandXdgToplevel&) = delete;
    WaylandXdgToplevel& operator=(WaylandXdgToplevel&&)      = default;

    [[nodiscard]]
    bool should_close() const {
        return m_should_close;
    }

    static const xdg_toplevel_listener m_listener;
};
} // namespace core::window::detail
