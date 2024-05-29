#include "main.h" // IWYU pragma: keep
#include "core/gui/window.h"

int main() {
    core::gui::Window game_window(
        config::window_width,
        config::window_height,
        config::game_name.data(),
        core::gui::WindowStyle::Windowed
    );
    game_window.clear();
    game_window.set_framerate(config::frame_rate);
    while (!game_window.should_close()) {
        game_window.display();
    }
    return 0;
}
