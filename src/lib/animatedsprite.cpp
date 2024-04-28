#include "lib/animatedsprite.h"
#include "config.h"

lib::AnimatedSprite::AnimatedSprite(
    std::string sheetfile, const int framecount, const int framerate
)
    : _texture(sheetfile), _framecount(framecount), _framerate(framerate),
      _delta(_texture.width / _framecount){};

void
lib::AnimatedSprite::Draw(raylib::Vector2 position)
{
    const int frameno =
        static_cast<int>(_ticks / (config::frame_rate / _framerate));
    const float             xcord = static_cast<float>(frameno * _delta);
    const raylib::Rectangle _draw_rect(
        xcord,
        0.0f,
        static_cast<float>(_delta),
        static_cast<float>(_texture.height)
    );
    _texture.Draw(_draw_rect, position);
    ++_ticks;
};

void
lib::AnimatedSprite::Draw(raylib::Vector2 position, int frameno)
{
    const float             xcord = static_cast<float>(frameno * _delta);
    const raylib::Rectangle _draw_rect(
        xcord,
        0.0f,
        static_cast<float>(_delta),
        static_cast<float>(_texture.height)
    );
    _texture.Draw(_draw_rect, position);
};

void
lib::AnimatedSprite::Draw(raylib::Vector2 position, const double time)
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
