#include "config.h"
#include "gui/window.h"
#include "objects/shroom.h"

int main() {
    gui::Window window(config::game_name);
    Shroom      player;
    while (gui::Window::next()) {
        gui::Window::start_frame();
        // while (gui::Keyboard::GetCharPressed()) {
        //     utils::log::debug("test");
        //     if (gui::Keyboard::IsKeyDown(Key::SPACE)) {
        //         player.toggle_state();
        //     };
        //     if (gui::Keyboard::IsKeyDown(Key::W)) {
        //         player.move({0, -10});
        //     }
        //     if (gui::Keyboard::IsKeyDown(Key::A)) {
        //         player.move({-10, 0});
        //     }
        //     if (gui::Keyboard::IsKeyDown(Key::S)) {
        //         player.move({0, 10});
        //     }
        //     if (gui::Keyboard::IsKeyDown(Key::D)) {
        //         player.move({10, 0});
        //     }
        // }
        player.draw();
        gui::Window::end_frame();
    }
    return 0;
}
