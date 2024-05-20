#include "core/animatedsprite.h"
#include "core/raycpp/rectangle.h"

void core::AnimatedSprite::draw(core::raycpp::Vector2 position) {
    const int frameno = static_cast<int>(_ticks / _framerate);
    core::AnimatedSprite::draw(position, frameno);
    ++_ticks;
}

void core::AnimatedSprite::draw(core::raycpp::Vector2 position, int frameno) {
    const auto xcord = static_cast<float>(frameno * _delta);

    const core::raycpp::Rectangle _draw_rect(
        xcord,
        0.0F,
        static_cast<float>(_delta),
        static_cast<float>(_texture.height)
    );
    _texture.Draw(_draw_rect, position);
}
