#include "config.h"
#include "utils/colours.h"
#include "utils/logger.h"
#include <raycpp/Rectangle.hpp>
#include <raycpp/Texture.hpp>
#include <raycpp/Window.hpp>

int
main()
{
    raylib::Window window(640, 360, "RayGame");
    window.Maximize();
    window.SetTargetFPS(config::frame_rate);

    constexpr int   medussy_frames    = 60;
    constexpr float medussy_framerate = 30;
    raylib::Texture medussy_spritesheet("resources/medussy-spritesheet.png");
    const int       medussy_delta = medussy_spritesheet.width / medussy_frames;

    while (!window.ShouldClose())
    {
        const int frameno = static_cast<int>(
                                (window.GetTime() * config::frame_rate) /
                                (config::frame_rate / medussy_framerate)
                            ) %
                            medussy_frames;
        const float xcord = static_cast<float>(frameno * medussy_delta);

        utils::log::trace("medussy_delta: " + std::to_string(medussy_delta));
        utils::log::trace("frameno: " + std::to_string(frameno));
        utils::log::trace("xcord: " + std::to_string(xcord));

        const raylib::Rectangle medussy_rect(
            xcord, 0.0f, float(medussy_delta), float(medussy_spritesheet.height)
        );

        window.BeginDrawing();
        window.ClearBackground();

        medussy_spritesheet.Draw(medussy_rect, raylib::Vector2{0, 0});

        window.DrawFPS(0, 0);
        window.EndDrawing();
    }
    return 0;
}

class AnimatedSprite
{
public:
    AnimatedSprite(
        std::string sheetfile, const int framecount, const int framerate
    )
        : _texture(sheetfile), _framecount(framecount), _framerate(framerate){};
    void Draw();

private:
    const raylib::Texture _texture;
    const int             _framecount;
    const int             _framerate;
};
