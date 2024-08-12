#pragma once

namespace core::window::wayland {
class WaylandWindow;

class Region {
    friend WaylandWindow;
    Region();

public:
    ~Region();
    Region operator+(const Region&);
};

} // namespace core::window::wayland
