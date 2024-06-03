#include "core/texture.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/gui/backend.h"
#include "core/math.h"

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

    // clang-format off
    const Quad<Vec2<float32>> vert{
        {static_cast<float32>(pos_x),          static_cast<float32>(pos_y)},
        {static_cast<float32>(pos_x + _width), static_cast<float32>(pos_y)},
        {static_cast<float32>(pos_x),          static_cast<float32>(pos_y + _height)},
        {static_cast<float32>(pos_x + _width), static_cast<float32>(pos_y + _height)},
    };
    // clang-format on
    const Quad<Vec2<float32>> tex = vert;

    draw(vert, tex);
}

void core::Texture::draw(int_t pos_x, int_t pos_y, deg_t rot_d) {
    const float32 rot_rad = math::deg2rad(rot_d);
    const float32 sin_rot = sinf(rot_rad);
    const float32 cos_rot = cosf(rot_rad);
    const auto posxf = static_cast<float32>(pos_x);
    const auto posyf = static_cast<float32>(pos_y);
    const auto fwidth = static_cast<float32>(_width);
    const auto fheight = static_cast<float32>(_height);

    Quad<Vec2<float32>> vert{};

    vert.tl.x = posxf + -posxf * cos_rot - -posyf * sin_rot;
    vert.tl.y = posyf + -posxf * sin_rot + -posyf * cos_rot;

    vert.tr.x = posxf + (-posxf + fwidth) * cos_rot - -posyf * sin_rot;
    vert.tr.y = posyf + (-posxf + fwidth) * sin_rot + -posyf * cos_rot;

    vert.bl.x = posxf + -posxf * cos_rot - (-posyf + fheight) * sin_rot;
    vert.bl.y = posyf + -posxf * sin_rot + (-posyf + fheight) * cos_rot;

    vert.br.x = posxf + (-posxf + fwidth) * cos_rot - (-posyf + fheight) * sin_rot;
    vert.br.y = posyf + (-posxf + fwidth) * sin_rot + (-posyf + fheight) * cos_rot;

    const Quad<Vec2<float32>> tex = vert;
    draw(vert, tex);
}

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
