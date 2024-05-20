#pragma once

#include "core/raycpp/textureunmanaged.h"

namespace core::raycpp {
class Texture: public TextureUnmanaged {
public:
    using TextureUnmanaged::TextureUnmanaged;
    Texture(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&& other) noexcept;
    ~Texture();
};

} // namespace core::raycpp
