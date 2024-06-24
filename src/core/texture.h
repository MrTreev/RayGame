#pragma once
#include "core/image.h"

namespace core {

class Texture {
private:
    uint32_t m_id;
    int32_t  m_width;
    int32_t  m_height;
    int32_t  m_n_mipmaps;

public:
    explicit Texture(const core::Image& image);

    Texture()                           = delete;
    Texture(const Texture&)             = delete;
    Texture(Texture&& other)            = default;
    Texture& operator=(const Texture&)  = delete;
    Texture& operator=(Texture&& other) = default;
    ~Texture();

    void load();
    void unload();

    void draw(Vec2<int32_t> pos);
    void draw(Vec2<int32_t> pos, uint8_t scale);
    void draw(Vec2<int32_t> pos, float scale);
    void draw(Vec2<int32_t> pos, deg_t rot_d, float scale);
    void draw(Vec2<int32_t> pos, Rect<int32_t> rect);

private:
    void draw(const Quad<Vec2<float>>& vert, const Quad<Vec2<float>>& tex);
    void print_info();
};

} // namespace core
