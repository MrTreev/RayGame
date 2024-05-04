#include "config.h"
#include "objects/shroom.h"
#include "utils/input.h"
#include "utils/logger.h"
#include <raycpp/Keyboard.hpp>
#include <raycpp/Window.hpp>

int main() {
    raylib::Window window(
        config::window_width,
        config::window_height,
        config::game_name
    );
    window.Maximize();
    window.SetTargetFPS(config::frame_rate);

    Shroom player;

    while (!window.ShouldClose()) {
        window.BeginDrawing();
        window.ClearBackground();
        using input::keyboard::Key;
        while (raylib::Keyboard::GetCharPressed()) {
            utils::log::debug("test");
            if (raylib::Keyboard::IsKeyDown(Key::SPACE)) {
                player.toggle_state();
            };
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
        window.DrawFPS(0, 0);
        window.EndDrawing();
    }
    return 0;
}
