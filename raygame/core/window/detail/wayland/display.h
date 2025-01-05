#pragma once
#include "raygame/core/types.h"
#include <wayland-client-core.h>

namespace core::window::detail {
class WaylandDisplay {
    wl_display* m_display{wl_display_connect(nullptr)};

public:
    WaylandDisplay();
};
} // namespace core::window::detail
