#include "core/window/wayland.h"

int main() {
    auto mywindow = core::window::WaylandWindow();
    while (mywindow.next_frame()) {}
}
