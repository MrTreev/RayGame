#pragma once
#include "core/image.h"
#include "core/types.h"

namespace core {

class Texture {
private:
    uint_t _id;
    int_t  _width;
    int_t  _height;
    int_t  _n_mipmaps;

public:
    explicit Texture(core::Image image);

    Texture()                           = delete;
    Texture(const Texture&)             = delete;
    Texture(Texture&& other)            = default;
    Texture& operator=(const Texture&)  = delete;
    Texture& operator=(Texture&& other) = default;
    ~Texture();

    void load();
    void unload();

    void draw(Vec2<int_t> pos);
    void draw(Vec2<int_t> pos, int_t scale);
    void draw(Vec2<int_t> pos, float_t scale);
    void draw(Vec2<int_t> pos, deg_t rot_d, float_t scale);
    void draw(Vec2<int_t> pos, Rect<int_t> rect);

private:
    void draw(const Quad<Vec2<float_t>>& vert, const Quad<Vec2<float_t>>& tex);
    void print_info();
};

} // namespace core
