#include "core/logger.h"
#include "core/windowimpl/wayland.h"
#include <format>

int main() {
    std::string tmp = std::format("test");
    core::log::debug("test");
    core::window::WaylandWindow my_window{};
    while (my_window.next_frame()) {}
}
