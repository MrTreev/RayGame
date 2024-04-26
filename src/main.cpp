#include "config.h"
#include "utils/colours.h"
#include "utils/logger.h"
#include <raycpp/Rectangle.hpp>
#include <raycpp/Texture.hpp>
#include <raycpp/Window.hpp>

class AnimatedSprite
{
public:
    AnimatedSprite(
        std::string sheetfile, const int framecount, const int framerate
    )
        : _texture(sheetfile), _framecount(framecount), _framerate(framerate),
          _delta(_texture.width / _framecount){};

    void
    Draw(raylib::Vector2 position, const double time)
    {
        const float xcord = static_cast<float>(
            static_cast<int>(_framerate * time) % _framecount * _delta
        );
        const raylib::Rectangle _draw_rect(
            xcord,
            0.0f,
            static_cast<float>(_delta),
            static_cast<float>(_texture.height)
        );

        _texture.Draw(_draw_rect, position);
    };

private:
    const raylib::Texture _texture;

    const int _framecount;
    const int _framerate;
    const int _delta;
};

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

    constexpr int oneussy_frames    = 34;
    constexpr int medussy_frames    = 60;
    constexpr int medussy_framerate = 30;

    AnimatedSprite medussy(
        "resources/medussy-spritesheet.png", medussy_frames, medussy_framerate
    );
    AnimatedSprite oneussy(
        "resources/oneussy-spritesheet.png", oneussy_frames, medussy_framerate
    );
    raylib::Texture medtest("resources/medussy-spritesheet.png");

    while (!window.ShouldClose())
    {
        window.BeginDrawing();
        window.ClearBackground();
        const double time = window.GetTime();

        utils::log::debug("time: " + std::to_string(time));
        medtest.Draw();
        // medussy.Draw({0, 0}, time);
        oneussy.Draw({0, 0}, time);

        window.DrawFPS(0, 0);
        window.EndDrawing();
    }
    return 0;
}
