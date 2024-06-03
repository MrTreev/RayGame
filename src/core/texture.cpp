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
    const auto posxf = static_cast<float32>(pos_x);
    const auto posyf = static_cast<float32>(pos_y);
    const auto poswf = static_cast<float32>(pos_x + _width);
    const auto poshf = static_cast<float32>(pos_y + _height);

    const Quad<Vec2<float32>> vert{
        {posxf, posyf},
        {posxf, poshf},
        {posxf, poshf},
        {poswf, posyf},
    };
    const Quad<Vec2<float32>> tex = vert;

    draw(vert, tex);
}

void core::Texture::draw(int_t pos_x, int_t pos_y, deg_t rot_d) {
    const float32 rot_rad = math::deg2rad(rot_d);
    const float32 sin_rot = sinf(rot_rad);
    const float32 cos_rot = cosf(rot_rad);
    const auto    posxf   = static_cast<float32>(pos_x);
    const auto    posyf   = static_cast<float32>(pos_y);
    const auto    fwidth  = static_cast<float32>(_width);
    const auto    fheight = static_cast<float32>(_height);

    Quad<Vec2<float32>> vert{
  // Top Left
        {posxf - posxf * cos_rot + posyf * sin_rot,
         posyf - posxf * sin_rot - posyf * cos_rot                            },
 // Bottom Left
        {posxf - (posxf * cos_rot) - ((fheight - posyf) * sin_rot),
         posyf - (posxf * sin_rot) + ((fheight - posyf) * cos_rot)            },
 // Bottom Right
        {posxf + ((fwidth - posxf) * cos_rot) - ((fheight + -posyf) * sin_rot),
         posyf + ((fwidth - posxf) * sin_rot) + ((fheight + -posyf) * cos_rot)},
 // Top Right
        {posxf + ((fwidth - posxf) * cos_rot) + (posyf * sin_rot),
         posyf + ((fwidth - posxf) * sin_rot) - (posyf * cos_rot)             },
    };

    const Quad<Vec2<float32>> tex = vert;
    draw(vert, tex);
}

void core::Texture::draw(int_t pos_x, int_t pos_y, deg_t rot_d, float32 scale) {
    const auto posxf   = static_cast<float32>(pos_x);
    const auto posyf   = static_cast<float32>(pos_y);
    const auto fwidth  = static_cast<float32>(_width);
    const auto fheight = static_cast<float32>(_height);

    float32       sin_rot = sinf(math::deg2rad(rot_d));
    float32       cos_rot = cosf(math::deg2rad(rot_d));
    Rect<float32> dest    = {posxf, posyf, fwidth * scale, fwidth * scale};

    tl.x = x + dx * cos_rot - dy * sin_rot;
    tl.y = y + dx * sin_rot + dy * cos_rot;

    tr.x = x + (dx + dest.width) * cos_rot - dy * sin_rot;
    tr.y = y + (dx + dest.width) * sin_rot + dy * cos_rot;

    bl.x = x + dx * cos_rot - (dy + dest.height) * sin_rot;
    bl.y = y + dx * sin_rot + (dy + dest.height) * cos_rot;

    br.x = x + (dx + dest.width) * cos_rot - (dy + dest.height) * sin_rot;
    br.y = y + (dx + dest.width) * sin_rot + (dy + dest.height) * cos_rot;
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
