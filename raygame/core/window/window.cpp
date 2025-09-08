#include "raygame/core/window/window.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/drawing/pixel.h"
#include "raygame/core/exception.h"
#include "raygame/core/logger.h"
#include "raygame/core/window/detail/backends.h"
#include <map>
#if defined(RAYGAME_GUI_BACKEND_RAYLIB)
#    include <raylib.h>
#endif

namespace {
namespace raylib {
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
} // namespace raylib

namespace wayland {} // namespace wayland

[[maybe_unused]]
constexpr core::config::GuiBackend COCOA = core::config::GuiBackend::COCOA;
[[maybe_unused]]
constexpr core::config::GuiBackend DWM     = core::config::GuiBackend::DWM;
constexpr core::config::GuiBackend RAYLIB  = core::config::GuiBackend::RAYLIB;
constexpr core::config::GuiBackend WAYLAND = core::config::GuiBackend::WAYLAND;
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
#elif defined(RAYGAME_GUI_BACKEND_WAYLAND)
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
    } else if constexpr (BACKEND == WAYLAND) {
        m_wl_shm_format = get_colour_format();
        m_wl_display    = wl_display_connect(nullptr);
        check_ptr(m_wl_display, "Display setup failed");
        m_wl_registry = wl_display_get_registry(m_wl_display);
        check_ptr(m_wl_registry, "Registry setup failed");
        wl_registry_add_listener(m_wl_registry, &m_wl_registry_listener, this);
        check_condition(wl_display_roundtrip(m_wl_display) != 0, "Display roundtrip failed");
        check_ptr(m_wl_shm, "shm global setup failed");
        check_ptr(m_wl_compositor, "compositor global setup failed");
        check_ptr(m_xdg_wm_base, "xdg_wm_base global setup failed");
        m_wl_surface = wl_compositor_create_surface(m_wl_compositor);
        check_ptr(m_wl_surface, "wl_surface setup failed");
        m_xdg_surface = xdg_wm_base_get_xdg_surface(m_xdg_wm_base, m_wl_surface);
        check_ptr(m_xdg_surface, "xdg_surface setup failed");
        m_xdg_toplevel = xdg_surface_get_toplevel(m_xdg_surface);
        check_ptr(m_xdg_toplevel, "xdg_toplevel setup failed");
        xdg_toplevel_add_listener(m_xdg_toplevel, &m_xdg_toplevel_listener, this);
        xdg_surface_add_listener(m_xdg_surface, &m_xdg_surface_listener, this);
        wl_surface_commit(m_wl_surface);
        log::trace("Surface Committed");
        while ((wl_display_dispatch(m_wl_display) != -1) && (!m_configured)) {
            log::error("Wayland display not configured");
        }
        log::trace("Display Dispatched");
        xdg_toplevel_set_title(m_xdg_toplevel, m_title.c_str());
        new_buffer();
        restyle();
        wl_surface_attach(m_wl_surface, m_wl_buffer, 0, 0);
        log::trace("Surface Attached");
        wl_surface_commit(m_wl_surface);
        log::trace("Surface Committed");
        m_wl_callback = wl_surface_frame(m_wl_surface);
        check_ptr(m_wl_callback, "Failed to create callback");
        wl_callback_add_listener(m_wl_callback, &m_wl_surface_frame_listener, this);
        log::trace("Return from Constructor");
    } else {
        condition::unreachable();
    }
}

core::window::Window::~Window() {
    core::log::debug("Destroying Window: {}", m_title);
    if constexpr (BACKEND == RAYLIB) {
        CloseWindow();
    } else if constexpr (BACKEND == WAYLAND) {
        m_buffer_width  = 0;
        m_buffer_height = 0;
        wl_buffer_destroy(m_wl_buffer);
        wl_surface_destroy(m_wl_surface);
        xdg_surface_destroy(m_xdg_surface);
        xdg_toplevel_destroy(m_xdg_toplevel);
    }
};

void core::window::Window::draw([[maybe_unused]] const drawing::ImageView& image) {
    if constexpr (BACKEND == RAYLIB) {
        const int       mipmaps     = 1;
        const int       imageformat = raylib::get_colour_format();
        const Texture2D texture     = [this, image, imageformat]() {
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
    } else if (BACKEND == WAYLAND) {
        constexpr auto clamp = [](const pos_t val) {
            return numeric_cast<dis_t>(std::max(pos_t(0), val));
        };
        constexpr auto domin = [](const dis_t max, const pos_t val) {
            return numeric_cast<dis_t>(std::min(numeric_cast<pos_t>(max), val));
        };
        const dis_t row_left  = clamp(image.top());
        const dis_t col_top   = clamp(image.left());
        const dis_t row_right = domin(height(), image.bottom());
        const dis_t col_bot   = domin(width(), image.right());
        if (std::cmp_greater(col_top, width()) || std::cmp_greater(row_left, height())) {
            return;
        }
        dis_t row{row_left};
        dis_t col{col_top};
        for (; row < row_right; ++row) {
            col = col_top;
            for (; col < col_bot; ++col) {
                const auto therow  = math::safe_sub<dis_t>(row, image.pos_y());
                const auto thecol  = math::safe_sub<dis_t>(col, image.pos_x());
                m_pixbuf[row, col] = image.at(therow, thecol);
            }
        }
        log::debug("Drawn: {} rows, {} cols", row - row_left, col - col_top);
    } else {
        condition::unreachable();
    }
}

void core::window::Window::restyle([[maybe_unused]] WindowStyle style) {
    if constexpr (BACKEND == RAYLIB) {
    } else if (BACKEND == WAYLAND) {
        switch (style) {
        case WindowStyle::Windowed:
            xdg_toplevel_unset_fullscreen(m_xdg_toplevel);
            xdg_toplevel_unset_maximized(m_xdg_toplevel);
            return;
        case WindowStyle::WindowedFullscreen:
            xdg_toplevel_unset_fullscreen(m_xdg_toplevel);
            xdg_toplevel_set_maximized(m_xdg_toplevel);
            return;
        case WindowStyle::Fullscreen: xdg_toplevel_set_fullscreen(m_xdg_toplevel, nullptr); return;
        }
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
    if constexpr (core::config::TIME_FRAMES) {
        frame_time_start();
    }
    if (!should_close()) {
        render_frame();
    }
    if constexpr (core::config::TIME_FRAMES) {
        frame_time_end();
    }
    return !should_close();
}

bool core::window::Window::should_close() const {
    if constexpr (BACKEND == RAYLIB) {
        return WindowShouldClose();
    } else if (BACKEND == WAYLAND) {
        return m_should_close;
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
