#include "core/texture.h" // IWYU pragma: keep
#include "core/backend.h"
#include "core/logger.h"
#include "core/math.h"
#if defined(RAYGAME_BACKEND_RAYLIB)
#    include <raylib.h>
#endif

#if defined(RAYGAME_BACKEND_RAYLIB)

constexpr int RG_PIXELFORMAT = RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

#    define RL_TO_CORE(rl)                                                     \
        _id        = (rl).id;                                                  \
        _width     = (rl).width;                                               \
        _height    = (rl).height;                                              \
        _n_mipmaps = (rl).mipmaps;                                             \
        assert((rl).format == RG_PIXELFORMAT)

void core::Texture::print_info() {
    const ::Texture tmp_tex =
        {_id, _width, _height, RG_PIXELFORMAT, _n_mipmaps};
    const std::string varmsg = std::format(
        "Texture ready: {}, id: {}, width: {}, height: {}, mipmaps: {}",
        ::IsTextureReady(tmp_tex),
        _id,
        _width,
        _height,
        _n_mipmaps
    );
    core::log::debug(varmsg);
}

core::Texture::Texture(core::Image image)
    : _id(rlLoadTexture(
        image.data(),
        image.width(),
        image.height(),
        RG_PIXELFORMAT,
        image.n_mipmaps()
    ))
    , _width(image.width())
    , _height(image.height())
    , _n_mipmaps(image.n_mipmaps()) {
    core::log::debug("creating texture");
    rlGenTextureMipmaps(_id, _width, _height, RG_PIXELFORMAT, &_n_mipmaps);
    const std::string msg = std::format("Texture created: {}", _id);
    core::log::debug(msg);
    print_info();
}

core::Texture::~Texture() {
    if (_id != 0) {
        ::rlUnloadTexture(_id);
        _id = 0;
    }
}

void core::Texture::draw(Vec2<int32_t> pos) {
    condition::pre_condition((_id != 0), "Texture._id != 0");
    condition::pre_condition((_width != 0), "Texture._width != 0");
    condition::pre_condition((_height != 0), "Texture._height != 0");
    const auto posxf = core::math::numeric_cast<float>(pos.x);
    const auto posyf = core::math::numeric_cast<float>(pos.y);
    const auto poswf = core::math::numeric_cast<float>(pos.x + _width);
    const auto poshf = core::math::numeric_cast<float>(pos.y + _height);
    const Quad<Vec2<float>> vert{
        {posxf, posyf},
        {posxf, poshf},
        {poswf, poshf},
        {poswf, posyf},
    };
    const Quad<Vec2<float>> tex = vert;
    log::debug(std::format(
        "tex: ({}, {}), ({}, {}), ({}, {}), ({}, {})",
        tex.tl.x,
        tex.tl.y,
        tex.bl.x,
        tex.bl.y,
        tex.br.x,
        tex.br.y,
        tex.tr.x,
        tex.tr.y
    ));
    draw(vert, tex);
}

void core::Texture::draw(Vec2<int32_t> pos, float scale) {
    condition::pre_condition((_id != 0), "Texture._id != 0");
    condition::pre_condition((_width != 0), "Texture._width != 0");
    condition::pre_condition((_height != 0), "Texture._height != 0");
    const auto posxf = core::math::numeric_cast<float>(pos.x);
    const auto posyf = core::math::numeric_cast<float>(pos.y);
    const auto poswf = core::math::numeric_cast<float>(pos.x + _width);
    const auto poshf = core::math::numeric_cast<float>(pos.y + _height);

    const Quad<Vec2<float>> vert{
        {posxf,         posyf        },
        {posxf,         poshf * scale},
        {poswf * scale, poshf * scale},
        {poswf * scale, posyf        },
    };
    const Quad<Vec2<float>> tex{
        {posxf, posyf},
        {posxf, poshf},
        {poswf, poshf},
        {poswf, posyf},
    };

    draw(vert, tex);
}

void core::Texture::draw(
    const Quad<Vec2<float>>& vert,
    const Quad<Vec2<float>>& tex
) {
    condition::pre_condition((_id != 0), "Texture._id != 0");
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

#elif defined(RAYGAME_BACKEND_SDL)

core::Texture::Texture(core::Image image) {}

core::Texture::~Texture() {}

void core::Texture::load() {}

void core::Texture::unload() {}

void core::Texture::draw(Vec2<int32_t> pos) {}

void core::Texture::draw(Vec2<int32_t> pos, uint8_t scale) {}

void core::Texture::draw(Vec2<int32_t> pos, float scale) {}

void core::Texture::draw(Vec2<int32_t> pos, deg_t rot_d, float scale) {}

void core::Texture::draw(Vec2<int32_t> pos, Rect<int32_t> rect) {}

void core::Texture::draw(
    const core::Quad<Vec2<float>>& vert,
    const core::Quad<Vec2<float>>& tex
) {}

void core::Texture::print_info() {}

#endif
