#include "config.h"
#include "objects/shroom.h"
#include "raylib/window.h"

int main() {
    raylib::Window window(config::game_name);
    Shroom         player;
    while (!raylib::Window::ShouldClose()) {
        raylib::Window::BeginDrawing();
        raylib::Window::ClearBackground();
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
        raylib::Window::EndDrawing();
    }
    return 0;
}
