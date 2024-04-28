#include "config.h"
#include "objects/shroom.h"
#include "utils/input.h"
#include "utils/logger.h"
#include <raycpp/Keyboard.hpp>
#include <raycpp/Window.hpp>

int
main()
{
    raylib::Window window(
        config::start_window_width,
        config::start_window_height,
        config::game_name
    );
    window.Maximize();
    window.SetTargetFPS(config::frame_rate);
    Shroom player;

    while (!window.ShouldClose())
    {
        window.BeginDrawing();
        window.ClearBackground();
        const double time = window.GetTime();
        utils::log::debug("time: " + std::to_string(time));
        using input::keyboard::Key;
        while (raylib::Keyboard::GetCharPressed())
        {
            if (raylib::Keyboard::IsKeyDown(Key::SPACE))
            {
                player.action(ShroomActs::hide);
            };
            if (raylib::Keyboard::IsKeyDown(Key::W))
            {
                player.move({0, -10});
            }
            if (raylib::Keyboard::IsKeyDown(Key::A))
            {
                player.move({-10, 0});
            }
            if (raylib::Keyboard::IsKeyDown(Key::S))
            {
                player.move({0, 10});
            }
            if (raylib::Keyboard::IsKeyDown(Key::D))
            {
                player.move({10, 0});
            }
        }

        player.draw();
        window.DrawFPS(0, 0);
        window.EndDrawing();
    }
    return 0;
}
