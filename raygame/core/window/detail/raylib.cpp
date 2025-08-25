#include "raygame/core/window/detail/raylib.h"
#include "raygame/core/drawing/image.h"
#include "raygame/core/exception.h"
#include "raygame/core/logger.h"
#include "raygame/core/math/numeric_cast.h"

#if defined(RAYGAME_GUI_BACKEND_RAYLIB)
RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
RAYGAME_CLANG_SUPPRESS_WARNING("-Wundef")
#    include <raylib.h>
RAYGAME_CLANG_SUPPRESS_WARNING_POP
#endif

namespace {
[[maybe_unused]]
PixelFormat get_colour_format() {
    using core::colour::rgba;
    using std::bit_cast;
    constexpr auto RVAL      = 0b00000000;
    constexpr auto GVAL      = 0b11111111;
    constexpr auto BVAL      = 0b00111100;
    constexpr auto AVAL      = 0b11000011;
    constexpr auto RGBA      = 0b00000000'11111111'00111100'11000011;
    constexpr auto BGRA      = 0b00111100'11111111'00000000'11000011;
    constexpr auto ABGR      = 0b11000011'00111100'11111111'00000000;
    constexpr auto ARGB      = 0b11000011'00000000'11111111'00111100;
    constexpr auto colourval = rgba(RVAL, GVAL, BVAL, AVAL);
    switch (bit_cast<uint32_t>(colourval)) {
    case (ARGB):
        core::log::debug("Colour Format: ARGB");
        throw core::exception::Exception("Invalid pixel format for raylib");
    case (ABGR):
        core::log::debug("Colour Format: ABGR");
        throw core::exception::Exception("Invalid pixel format for raylib");
    case (BGRA):
        core::log::debug("Colour Format: BGRA");
        throw core::exception::Exception("Invalid pixel format for raylib");
    case (RGBA): core::log::debug("Colour Format: RGBA"); return PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    default:
        throw std::invalid_argument(
            std::format(
                "Could not determine colour format:\n"
                "functdef: {:0>32b}\n"
                "RGBA DEF: {:0>32b}\n"
                "RGBA set: {:0>32b}{:0>32b}{:0>32b}{:0>32b}\n"
                "BYTE NO:  00000000111111112222222233333333\n",
                bit_cast<uint32_t>(colourval),
                RGBA,
                colourval.m_alpha,
                colourval.m_blue,
                colourval.m_green,
                colourval.m_red
            )
        );
    }
}

} // namespace

namespace core::window::detail {
RaylibWindowImpl::RaylibWindowImpl(Vec2<size_t> size, std::string title, WindowStyle style)
    : WindowImpl(size, std::move(title), style) {
    InitWindow(
        math::numeric_cast<int>(width()),
        math::numeric_cast<int>(height()),
        get_title().c_str()
    );
}

RaylibWindowImpl::~RaylibWindowImpl() {
    CloseWindow();
}

void RaylibWindowImpl::draw(const drawing::ImageView& image) {
    constexpr int   mipmaps     = 1;
    constexpr int   imageformat = 1;
    const Texture2D texture     = [this, image]() {
        //NOLINTNEXTLINE(*-cast)
        if (m_imgs.contains(reinterpret_cast<const void*>(image.data()))) {
            return (Texture2D){m_imgs[image.data()],
                               math::numeric_cast<int>(image.width()),
                               math::numeric_cast<int>(image.height()),
                               mipmaps,
                               imageformat};
        }
        const drawing::ImageView imagecpy = image;
        const Image              this_image{
            //NOLINTNEXTLINE(*-cast)
            reinterpret_cast<void*>(const_cast<Pixel*>(imagecpy.data())),
            math::numeric_cast<int>(image.width()),
            math::numeric_cast<int>(image.height()),
            mipmaps,
            imageformat
        };
        const Texture2D tex  = LoadTextureFromImage(this_image);
        m_imgs[image.data()] = tex.id;
        return tex;
    }();
    DrawTexture(
        texture,
        math::numeric_cast<int>(image.pos_x()),
        math::numeric_cast<int>(image.pos_y()),
        RAYWHITE
    );
}

void RaylibWindowImpl::restyle([[maybe_unused]] WindowStyle style) {}

void RaylibWindowImpl::render_frame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
}

[[nodiscard]]
bool RaylibWindowImpl::next_frame() {
    if (!should_close()) {
        render_frame();
    }
    return !should_close();
}

[[nodiscard]]
bool RaylibWindowImpl::should_close() const {
    return WindowShouldClose();
}

} // namespace core::window::detail
