#include "core/raycpp/texture.h"

core::raycpp::Texture::Texture(Texture&& other) noexcept {
    set(other);

    other.id      = 0;
    other.width   = 0;
    other.height  = 0;
    other.mipmaps = 0;
    other.format  = 0;
}

core::raycpp::Texture::~Texture() {
    Unload();
}

core::raycpp::Texture& core::raycpp::Texture::operator=(Texture&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.id      = 0;
    other.width   = 0;
    other.height  = 0;
    other.mipmaps = 0;
    other.format  = 0;

    return *this;
}
