#include "raygame/core/window/window.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/drawing/pixel.h"
#include "raygame/core/exception.h"
#include "raygame/core/logger.h"
#include "raygame/core/window/detail/backends.h"
#include "raygame/core/window/detail/raylib.h"
#include <map>
#if defined(RAYGAME_GUI_BACKEND_RAYLIB)
#    include <raylib.h>
#endif

namespace {
namespace raylib {
constexpr PixelFormat get_colour_format() {
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
} // namespace raylib

[[maybe_unused]]
constexpr core::config::GuiBackend RAYLIB = core::config::GuiBackend::RAYLIB;
[[maybe_unused]]
constexpr core::config::GuiBackend COCOA = core::config::GuiBackend::COCOA;
[[maybe_unused]]
constexpr core::config::GuiBackend WAYLAND = core::config::GuiBackend::WAYLAND;
[[maybe_unused]]
constexpr core::config::GuiBackend DWM = core::config::GuiBackend::DWM;
[[maybe_unused]]
constexpr core::config::GuiBackend BACKEND = []() {
    using core::condition::unimplemented;
    using core::config::GuiBackend;
    using core::config::OperatingSystem;
    if constexpr (core::config::BUILD_TYPE == core::config::BuildType::DEBUG) {
        return GuiBackend::RAYLIB;
    }
    switch (core::config::OPERATING_SYSTEM) {
    case OperatingSystem::ANDROID: unimplemented();
    case OperatingSystem::BSD:     [[fallthrough]];
    case OperatingSystem::HURD:    [[fallthrough]];
    case OperatingSystem::LINUX:   return GuiBackend::WAYLAND;
    case OperatingSystem::MAC:     return GuiBackend::COCOA;
    case OperatingSystem::QNX:     unimplemented();
    case OperatingSystem::WIN32:   [[fallthrough]];
    case OperatingSystem::WIN64:   return GuiBackend::DWM;
    }
}();
} // namespace

class core::window::Window::WindowData {
public:
#if defined(RAYGAME_GUI_BACKEND_RAYLIB)
    std::map<const void*, unsigned int> m_imgs;
#endif
};

core::window::Window::Window(Vec2<size_t> size, std::string title, WindowStyle style)
    : m_size(size)
    , m_title(std::move(title))
    , m_style(style) {
    if constexpr (BACKEND == RAYLIB) {
        InitWindow(
            math::numeric_cast<int>(width()),
            math::numeric_cast<int>(height()),
            get_title().c_str()
        );
    } else {
        condition::unreachable();
    }
}

core::window::Window::~Window() {
    core::log::debug("Destroying Window: {}", m_title);
    if constexpr (BACKEND == RAYLIB) {
        CloseWindow();
    }
};

void core::window::Window::draw([[maybe_unused]] const drawing::ImageView& image) {
    if constexpr (BACKEND == RAYLIB) {
        constexpr int   mipmaps     = 1;
        constexpr int   imageformat = raylib::get_colour_format();
        const Texture2D texture     = [this, image]() {
            //NOLINTNEXTLINE(*-cast)
            if (m_data->m_imgs.contains(reinterpret_cast<const void*>(image.data()))) {
                return (Texture2D){m_data->m_imgs[image.data()],
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
            const Texture2D tex{LoadTextureFromImage(this_image)};
            m_data->m_imgs[image.data()] = tex.id;
            return tex;
        }();
        DrawTexture(
            texture,
            math::numeric_cast<int>(image.pos_x()),
            math::numeric_cast<int>(image.pos_y()),
            RAYWHITE
        );
    } else {
        condition::unreachable();
    }
}

void core::window::Window::restyle([[maybe_unused]] WindowStyle style) {
    if constexpr (BACKEND == RAYLIB) {
    } else {
        condition::unreachable();
    }
}

void core::window::Window::render_frame() {
    if constexpr (BACKEND == RAYLIB) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    } else {
        condition::unreachable();
    }
}

bool core::window::Window::next_frame() {
    if (!should_close()) {
        render_frame();
    }
    return !should_close();
}

bool core::window::Window::should_close() const {
    if constexpr (BACKEND == RAYLIB) {
        return WindowShouldClose();
    } else {
        condition::unreachable();
    }
}

std::string core::window::Window::frame_stats() {
    return std::format(
        "Min Frame Time: {}\n"
        "Max Frame Time: {}\n"
        "Ave Frame Time: {}",
        m_counter.min(),
        m_counter.max(),
        m_counter.average()
    );
}

void core::window::Window::set_size(Vec2<size_t> size) {
    m_size = size;
}

void core::window::Window::set_title(std::string title) {
    m_title = std::move(title);
}

void core::window::Window::set_style(WindowStyle style) {
    m_style = style;
}
