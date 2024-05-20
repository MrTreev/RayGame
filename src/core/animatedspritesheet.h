#pragma once
#include "core/raycpp/rectangle.h"
#include "core/raycpp/texture.h"
#include <array>
#include <cstddef>

namespace core {
template<int height>
class AnimatedSpriteSheet {
private:
    const core::raycpp::Texture   _texture;
    const std::array<int, height> _framecount;
    const std::array<int, height> _framerate;
    const int                     _delta_height;
    const int                     _delta_width;
    int                           _ticks{0};

public:
    AnimatedSpriteSheet(
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

    AnimatedSpriteSheet()                                      = delete;
    ~AnimatedSpriteSheet()                                     = default;
    AnimatedSpriteSheet(const AnimatedSpriteSheet&)            = delete;
    AnimatedSpriteSheet(const AnimatedSpriteSheet&&)           = delete;
    AnimatedSpriteSheet operator=(const AnimatedSpriteSheet&)  = delete;
    AnimatedSpriteSheet operator=(const AnimatedSpriteSheet&&) = delete;

    void draw(core::raycpp::Vector2 position, int animation_no) {
        const int frameno = static_cast<int>(
            _ticks / _framerate[static_cast<std::size_t>(animation_no)]
        );
        draw(position, animation_no, frameno);
        ++_ticks;
    };

    void draw(core::raycpp::Vector2 position, int animation_no, int frameno) {
        const auto xcord = static_cast<float>(frameno * _delta_width);
        const auto ycord = static_cast<float>(animation_no * _delta_height);
        const core::raycpp::Rectangle _draw_rect(
            xcord,
            ycord,
            static_cast<float>(_delta_width),
            static_cast<float>(static_cast<float>(_texture.height) / height)
        );
        _texture.Draw(_draw_rect, position);
    };
};

} // namespace core
