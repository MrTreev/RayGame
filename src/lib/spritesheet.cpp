#include "lib/spritesheet.h"
#include "raylib/rectangle.h"

template<std::size_t height>
lib::SpriteSheet<height>::SpriteSheet(
    const std::string&             sheetfile,
    const std::array<int, height>& framecount,
    const std::array<int, height>& framerate,
    const int&                     frameswide
)
    : _texture(sheetfile)
    , _framecount(framecount)
    , _framerate(framerate)
    , _delta_height(_texture.height / height)
    , _delta_width(_texture.width / frameswide){};

template<std::size_t height>
void lib::SpriteSheet<height>::draw(
    raylib::Vector2 position,
    std::size_t     animation_no
) {
    const int frameno = static_cast<int>(_ticks / _framerate);
    lib::SpriteSheet<height>::draw(position, animation_no, frameno);
    ++_ticks;
};

template<std::size_t height>
void lib::SpriteSheet<height>::draw(
    raylib::Vector2 position,
    std::size_t     animation_no,
    int             frameno
) {
    const auto              xcord = static_cast<float>(frameno * _delta_width);
    const raylib::Rectangle _draw_rect(
        xcord,
        (animation_no * _delta_height),
        static_cast<float>(_delta_width),
        static_cast<float>(_texture.height)
    );
    _texture.Draw(_draw_rect, position);
};
