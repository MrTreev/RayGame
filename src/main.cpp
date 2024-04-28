#include "config.h"
#include "utils/colours.h"
#include "utils/logger.h"
#include "objects/evilwizard.h"
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
    EvilWizard wizard;

    while (!window.ShouldClose())
    {
        window.BeginDrawing();
        window.ClearBackground();
        const double time = window.GetTime();
        utils::log::debug("time: " + std::to_string(time));

        wizard.draw_idle(time);

        window.DrawFPS(0, 0);
        window.EndDrawing();
    }
    return 0;
}
