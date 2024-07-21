#include "core/logger.h"
#include "core/window.h"
#include "core/windowimpl/wayland.h"
#include <string_view>
#include <unistd.h>

int main() {
    const std::string_view filename = "etc/images/Weapon-Asset-Part1.png";
    core::Window
        game_window{3840, 2160, "RayGame", core::WindowStyle::Fullscreen};
    while (!game_window.should_close()) {
        core::log::debug("Tick");
        memset(
            core::window::wayland::wayland_state.m_shm_data,
            0x00'00'00'FFU,
            (3840 * 2160 * 4)
        );
        game_window.render();
    }
}
