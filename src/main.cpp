#include "core/colours.h"
// #include "core/logger.h"
#include "core/window.h"
#include "core/windowimpl/wayland.h"

int main() {
    constexpr size_t       screen_width  = 640;
    constexpr size_t       screen_height = 480;
    constexpr size_t       bufsize       = screen_width * screen_height;
    constexpr size_t       delta         = (screen_width * screen_height * 4);
    const std::string_view filename      = "etc/images/Weapon-Asset-Part1.png";
    core::Window           game_window{
        screen_width,
        screen_height,
        "RayGame",
        core::WindowStyle::Windowed
    };
    std::array<core::Pixel, bufsize> pixbuf{0};
    pixbuf.fill(core::colours::BLACK);
    while (!core::Window::should_close()) {
        // core::log::debug("Tick");
        std::memcpy(
            core::window::wayland::wayland_state.m_shm_data,
            pixbuf.data(),
            pixbuf.size() * sizeof(core::Pixel)
        );
        game_window.render();
    }
}
