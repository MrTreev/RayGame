#pragma once
#include "raygame/core/types.h"
#include <wayland-client.h>

namespace core::window::detail {
class WaylandRegistry {
    wl_registry* m_wl_registry{nullptr};

    static void global(
        void*        data,
        wl_registry* registry,
        uint32_t     name,
        const char*  interface,
        uint32_t     version
    );

    static void global_remove(
        void*        data,
        wl_registry* registry,
        uint32_t     name
    );

public:
    static const wl_registry_listener listener;
};
} // namespace core::window::detail
