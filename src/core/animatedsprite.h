#pragma once
#include "core/raycpp/texture.h"
#include <string>

namespace core {

class AnimatedSprite {
private:
    const core::raycpp::Texture _texture;
    const int             _framecount;
    const int             _framerate;
    const int             _delta;
    int                   _ticks{0};

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

    void draw(core::raycpp::Vector2 position);
    void draw(core::raycpp::Vector2 position, int frameno);

    [[nodiscard]]
    inline int fps() const {
        return _framerate;
    };
};

} // namespace lib
