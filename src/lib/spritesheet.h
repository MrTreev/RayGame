#pragma once
#include "raylib/rectangle.h"
#include "raylib/texture.h"
#include <array>
#include <cstddef>

namespace lib {
template<int height>
class SpriteSheet {
private:
    const raylib::Texture         _texture;
    const std::array<int, height> _framecount;
    const std::array<int, height> _framerate;
    const int                     _delta_height;
    const int                     _delta_width;
    int                           _ticks{0};

public:
    SpriteSheet(
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

    SpriteSheet()                              = delete;
    ~SpriteSheet()                             = default;
    SpriteSheet(const SpriteSheet&)            = delete;
    SpriteSheet(const SpriteSheet&&)           = delete;
    SpriteSheet operator=(const SpriteSheet&)  = delete;
    SpriteSheet operator=(const SpriteSheet&&) = delete;

    void draw(raylib::Vector2 position, int animation_no) {
        const int frameno = static_cast<int>(
            _ticks / _framerate[static_cast<std::size_t>(animation_no)]
        );
        lib::SpriteSheet<height>::draw(position, animation_no, frameno);
        ++_ticks;
    };

    void draw(raylib::Vector2 position, int animation_no, int frameno) {
        const auto xcord = static_cast<float>(frameno * _delta_width);
        const auto ycord = static_cast<float>(animation_no * _delta_height);
        const raylib::Rectangle _draw_rect(
            xcord,
            ycord,
            static_cast<float>(_delta_width),
            static_cast<float>(static_cast<float>(_texture.height) / height)
        );
        _texture.Draw(_draw_rect, position);
    };
};

} // namespace lib
