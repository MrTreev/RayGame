#include "config.h"
#include "objects/shroom.h"
#include "raylib/input.h"
#include "raylib/keyboard.h"
#include "raylib/window.h"
#include "utils/logger.h"

int main() {
    raylib::Window window(config::game_name);
    raylib::Window::SetTargetFPS(config::frame_rate);
    Shroom player;
    while (!raylib::Window::ShouldClose()) {
        raylib::Window::BeginDrawing();
        raylib::Window::ClearBackground();
        while (raylib::Keyboard::GetCharPressed()) {
            using raylib::Key;
            utils::log::debug("test");
            // if (raylib::Keyboard::IsKeyDown(Key::SPACE)) {
            //     player.toggle_state();
            // };
            if (raylib::Keyboard::IsKeyDown(Key::W)) {
                player.move({0, -10});
            }
            if (raylib::Keyboard::IsKeyDown(Key::A)) {
                player.move({-10, 0});
            }
            if (raylib::Keyboard::IsKeyDown(Key::S)) {
                player.move({0, 10});
            }
            if (raylib::Keyboard::IsKeyDown(Key::D)) {
                player.move({10, 0});
            }
        }
        player.draw();
        raylib::Window::DrawFPS();
        raylib::Window::EndDrawing();
    }
    return 0;
}
