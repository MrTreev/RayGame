#pragma once
#include <raycpp/Rectangle.hpp>
#include <raycpp/Texture.hpp>

namespace lib
{

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
            (static_cast<int>(_framerate * time) % _framecount) * _delta
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

} // namespace lib
