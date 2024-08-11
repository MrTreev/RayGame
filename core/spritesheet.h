#pragma once
#include "core/texture.h"
#include <string>

namespace core {

class SpriteSheet {
private:
    core::Texture m_texture;

public:
    SpriteSheet(
        const std::string& filename,
        const size_t&      width,
        const size_t&      height
    );
};

} // namespace core
