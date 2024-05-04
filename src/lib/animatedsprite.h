#pragma once
#include <raycpp/Rectangle.hpp>
#include <raycpp/Texture.hpp>

namespace lib {

class AnimatedSprite {
public:
    AnimatedSprite(
        std::string sheetfile,
        const int   framecount,
        const int   framerate
    );
    void draw(raylib::Vector2 position);
    void draw(raylib::Vector2 position, int frameno);
    void draw(raylib::Vector2 position, const double time);

    inline int fps() {
        return _framerate;
    };

private:
    const raylib::Texture _texture;

    const int _framecount{0};
    const int _framerate;
    const int _delta;
    int       _ticks{0};
};

} // namespace lib
