#pragma once
#include "core/image.h"
#include "core/types.h"

namespace core {

class Texture {
private:
    uint64_t id;
    int64_t  width;
    int64_t  height;
    int64_t  mipmaps;
    int64_t  format;

public:
    explicit Texture(core::Image);

    Texture();
    Texture(const Texture&)             = delete;
    Texture(Texture&& other)            = default;
    Texture& operator=(const Texture&)  = delete;
    Texture& operator=(Texture&& other) = default;
    ~Texture()                          = default;

    void load();
    void unload();
    void draw(size_t posX, size_t posY);
    void draw(size_t posX, size_t posY, rot_deg rotation);
};

} // namespace core
