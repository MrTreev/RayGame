#include "config.h"
#include "gui/input.h"
#include "gui/window.h"
#include "objects/shroom.h"
#include "utils/logger.h"
void draw_func();

int main() {
    gui::Window window(config::game_name);
    Shroom      player;
    window.start_frame();
    draw_func();
    using gui::input::keyboard::Key;
    // while (raylib::Keyboard::GetCharPressed()) {
    //     utils::log::debug("test");
    //     if (raylib::Keyboard::IsKeyDown(Key::SPACE)) {
    //         player.toggle_state();
    //     };
    //     if (raylib::Keyboard::IsKeyDown(Key::W)) {
    //         player.move({0, -10});
    //     }
    //     if (raylib::Keyboard::IsKeyDown(Key::A)) {
    //         player.move({-10, 0});
    //     }
    //     if (raylib::Keyboard::IsKeyDown(Key::S)) {
    //         player.move({0, 10});
    //     }
    //     if (raylib::Keyboard::IsKeyDown(Key::D)) {
    //         player.move({10, 0});
    //     }
    // }
    player.draw();
    window.end_frame();
    return 0;
};
