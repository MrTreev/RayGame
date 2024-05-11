#pragma once
#include "raylib/texture.h"
#include <array>

namespace lib {
template<std::size_t height>
class SpriteSheet {
private:
    const raylib::Texture             _texture;
    const std::array<int, height - 1> _framecount;
    const std::array<int, height - 1> _framerate;
    const int                         _delta_width;
    const int                         _delta_height;
    int                               _ticks{0};

public:
    SpriteSheet(
        const std::string&                 sheetfile,
        const std::array<int, height - 1>& framecount,
        const std::array<int, height - 1>& framerate,
        const int&                         frameswide
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

    void draw(raylib::Vector2 position, std::size_t animation_no);
    void draw(raylib::Vector2 position, std::size_t animation_no, int frameno);
};

} // namespace lib
