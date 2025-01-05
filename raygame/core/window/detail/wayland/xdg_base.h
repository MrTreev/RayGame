#pragma once
#include "raygame/core/condition.h"
#include "raygame/core/types.h"
#include <xdg-shell-client-protocol.h>

namespace core::window::detail {
class WaylandXdgBase {
    xdg_wm_base* m_base;
    static void  ping(void* data, xdg_wm_base* xdg_wm_base, uint32_t serial);

public:
    static const xdg_wm_base_listener m_listener;

    void bind(xdg_wm_base* base) {
        condition::check_ptr(base, "Cannot bind xdg_wm_base to nullptr");
        m_base = base;
    }
};
} // namespace core::window::detail
