// #include "core/logger.h"
#include "core/window.h"
#include <cstring>

int main() {
    constexpr size_t screen_width  = 640;
    constexpr size_t screen_height = 480;
    [[maybe_unused]]
    const std::string_view filename = "etc/images/Weapon-Asset-Part1.png";
    core::Window           game_window{
        screen_width,
        screen_height,
        "RayGame",
        core::WindowStyle::Windowed
    };
    while (!core::Window::should_close()) {
        // core::log::debug("Tick");
        game_window.render();
    }
}
