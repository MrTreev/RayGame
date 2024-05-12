#pragma once
#include "raylib/texture.h"
#include <array>

namespace lib {
template<std::size_t height>
class SpriteSheet {
private:
    const raylib::Texture               _texture;
    const std::array<const int, height> _framecount;
    const std::array<const int, height> _framerate;
    const int                           _delta_width;
    const int                           _delta_height;
    int                                 _ticks{0};

public:
    SpriteSheet<height>(
        const std::string&            sheetfile,
        std::array<const int, height> framecount,
        std::array<const int, height> framerate,
        const int&                    frameswide
    );

    SpriteSheet()                               = delete;
    ~SpriteSheet()                              = default;
    SpriteSheet(const SpriteSheet&)             = delete;
    SpriteSheet(const SpriteSheet&&)            = delete;
    SpriteSheet& operator=(const SpriteSheet&)  = delete;
    SpriteSheet& operator=(const SpriteSheet&&) = delete;

    void draw(raylib::Vector2 position, std::size_t animation_no);
    void draw(raylib::Vector2 position, std::size_t animation_no, int frameno);
};
} // namespace lib
