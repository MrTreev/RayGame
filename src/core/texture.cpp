#include "core/texture.h" // IWYU pragma: keep
#include "core/condition.h"
#include <rlgl.h>

constexpr int RG_PIXELFORMAT = RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

core::Texture::Texture(core::Image image)
    : _width(image.width())
    , _height(image.height())
    , _n_mipmaps(image.n_mipmaps()) {
    _id = rlLoadTexture(
        image.data(),
        _width,
        _height,
        RG_PIXELFORMAT,
        _n_mipmaps
    );
}

void core::Texture::draw(int_t pos_x, int_t pos_y) {
    condition::pre_condition((_width != 0), "Texture._width != 0");
    condition::pre_condition((_height != 0), "Texture._height != 0");

    const Quad<Vec2<float32>> vert{
        {static_cast<float32>(pos_x),          static_cast<float32>(pos_y)},
        {static_cast<float32>(pos_x + _width), static_cast<float32>(pos_y)},
        {static_cast<float32>(pos_x),          static_cast<float32>(pos_y + _height)},
        {static_cast<float32>(pos_x + _width), static_cast<float32>(pos_y + _height)}
    };
    const Quad<Vec2<float32>> tex{};

    draw(vert, tex);
}

void core::Texture::draw(int_t pos_x, int_t pos_y, deg_t rot_d) {}

void core::Texture::draw(int_t pos_x, int_t pos_y, deg_t rot_d, float32 scale) {
}

void core::Texture::draw(Quad<Vec2<float32>> vert, Quad<Vec2<float32>> tex) {
    rlSetTexture(_id);
    rlBegin(RL_QUADS);
    rlNormal3f(0.0F, 0.0F, 1.0F);

    // Top Left
    rlTexCoord2f(tex.tl.x, tex.tl.y);
    rlVertex2f(vert.tl.x, vert.tl.y);

    // Bottom Left
    rlTexCoord2f(tex.bl.x, tex.bl.y);
    rlVertex2f(vert.bl.x, vert.bl.y);

    // Bottom Right
    rlTexCoord2f(tex.br.x, tex.br.y);
    rlVertex2f(vert.br.x, vert.br.y);

    // Top Right
    rlTexCoord2f(tex.tr.x, tex.tr.y);
    rlVertex2f(vert.tr.x, vert.tr.y);

    rlEnd();
    rlSetTexture(0);
}
