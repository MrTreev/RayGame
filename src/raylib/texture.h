#pragma once

#include "raylib/textureunmanaged.h"

namespace raylib {
class Texture: public TextureUnmanaged {
public:
    using TextureUnmanaged::TextureUnmanaged;
    Texture(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&& other) noexcept;
    ~Texture();
};

} // namespace raylib
