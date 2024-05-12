#pragma once
#include "raylib/texture.h"
#include <array>

namespace lib {
template<std::size_t height>
class SpriteSheet {
private:
    const raylib::Texture         _texture;
    const std::array<int, height> _framecount;
    const std::array<int, height> _framerate;
    const int                     _delta_width;
    const int                     _delta_height;
    int                           _ticks{0};

public:
    SpriteSheet(
        const std::string&             sheetfile,
        const std::array<int, height>& framecount,
        const std::array<int, height>& framerate,
        const int&                     frameswide
    );

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
