#pragma once
#include <raycpp/Rectangle.hpp>
#include <raycpp/Texture.hpp>

namespace lib {

class AnimatedSprite {
public:
    AnimatedSprite(
        const std::string& sheetfile,
        const int&         framecount,
        const int&         framerate
    )
        : _texture(sheetfile)
        , _framecount(framecount)
        , _framerate(framerate)
        , _delta(_texture.width / _framecount){};

    AnimatedSprite()                                 = delete;
    ~AnimatedSprite()                                = default;
    AnimatedSprite(const AnimatedSprite&)            = delete;
    AnimatedSprite(const AnimatedSprite&&)           = delete;
    AnimatedSprite operator=(const AnimatedSprite&)  = delete;
    AnimatedSprite operator=(const AnimatedSprite&&) = delete;

    void draw(raylib::Vector2 position);
    void draw(raylib::Vector2 position, int frameno);

    [[nodiscard]]
    inline int fps() const {
        return _framerate;
    };

private:
    using Texture = raylib::Texture;

    const Texture _texture;
    const int     _framecount;
    const int     _framerate;
    const int     _delta;
    int           _ticks{0};
};

} // namespace lib
