#include "lib/animatedsprite.h"

void lib::AnimatedSprite::draw(raylib::Vector2 position) {
    const int frameno = static_cast<int>(_ticks / _framerate);
    lib::AnimatedSprite::draw(position, frameno);
    ++_ticks;
};

void lib::AnimatedSprite::draw(raylib::Vector2 position, int frameno) {
    const auto xcord = static_cast<float>(frameno * _delta);

    const raylib::Rectangle _draw_rect(
        xcord,
        0.0F,
        static_cast<float>(_delta),
        static_cast<float>(_texture.height)
    );
    _texture.Draw(_draw_rect, position);
};
