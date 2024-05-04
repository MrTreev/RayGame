#pragma once
#include "gui/colour.h"
#include "gui/vector.h"
#include "utils/logger.h"
#include <stdexcept>

namespace gui {

class Texture {
private:
    const ::Texture _texture;

    void Draw(int posX = 0, int posY = 0, Colour tint = colour::black) const {
        ::DrawTexture(_texture, posX, posY, tint);
    }

    void Draw(
        Rect         sourceRec,
        const Vec2d& position = {0, 0},
        Colour       tint     = colour::black
    ) const {
        ::DrawTextureRec(_texture, sourceRec, position, tint);
    }

public:
    explicit Texture(const std::string& fileName)
        : _texture(::LoadTexture(fileName.c_str())) {
        if (_texture.id == 0) {
            utils::log::fatal("Failed to create texture" + fileName);
            throw std::runtime_error("Failed to create texture");
        }
    };

    ~Texture() {
        if (_texture.id != 0) {
            ::UnloadTexture(_texture);
        }
    };

    Texture(const Texture&&)            = delete;
    Texture& operator=(const Texture&)  = delete;
    Texture(const Texture&)             = delete;
    Texture& operator=(const Texture&&) = delete;
};

} // namespace gui
