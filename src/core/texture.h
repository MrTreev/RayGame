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
    ~Texture()                          = default;

    void load();
    void unload();
    void draw(Vec2<int_t> pos);
    void draw(Vec2<int_t> pos, deg_t rot_d);
    void draw(Vec2<int_t> pos, deg_t rot_d, float32 scale);
    void draw(int_t pos_x, int_t pos_y);
    void draw(int_t pos_x, int_t pos_y, deg_t rot_d);
    void draw(int_t pos_x, int_t pos_y, deg_t rot_d, float32 scale);

private:
    void draw(Quad<Vec2<float32>> vert, Quad<Vec2<float32>> tex);
};

} // namespace core
