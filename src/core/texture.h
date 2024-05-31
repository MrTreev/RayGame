#pragma once
#include "core/types.h"
#include <cstdint>

namespace core {

class Texture {
private:
    uint64_t id;
    int64_t  width;
    int64_t  height;
    int64_t  mipmaps;
    int64_t  format;

public:
    Texture();
    Texture(const Texture&)             = delete;
    Texture(Texture&& other)            = default;
    Texture& operator=(const Texture&)  = delete;
    Texture& operator=(Texture&& other) = default;
    ~Texture()                          = default;
};

} // namespace core
