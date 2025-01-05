#include "raygame/core/window/detail/wayland.h"
#if defined(RAYGAME_GUI_BACKEND_WAYLAND)
#    include "raygame/core/condition.h"
#    include "raygame/core/drawing/colour.h"
#    include "raygame/core/logger.h"
#    include "raygame/core/math/random.h"
#    include <algorithm>
#    include <fcntl.h>
#    include <sys/mman.h>
#    include <unistd.h>
#    include <utility>
#    include <wayland-client-core.h>
#    include <wayland-client-protocol.h>
#    include <xdg-shell-client-protocol.h>
#    include <xkbcommon/xkbcommon.h>

namespace {
using core::condition::check_condition;
using core::condition::check_ptr;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;
using core::math::safe_mult;

constexpr size_t COLOUR_CHANNELS = 4;

constexpr std::string_view alnum =
    "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

std::string random_string(
    const size_t&      length,
    const std::string& valid_chars = {alnum.data(), alnum.length()}
) {
    std::string  ret;
    const size_t charlen = valid_chars.size() - 1;
    std::generate_n(std::back_inserter(ret), length, [&] {
        return valid_chars[core::math::rand<size_t>(0, charlen)];
    });
    return ret;
}

int create_shm_file() {
    constexpr int N_RETRIES = 100;
    constexpr int RAND_LEN  = 6;
    for (int retries = N_RETRIES; retries > 0; --retries) {
        std::string name("/wl_shm-");
        name.append(random_string(RAND_LEN));
        const int shm_fd =
            shm_open(name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0600);
        if (shm_fd >= 0) {
            shm_unlink(name.c_str());
            return shm_fd;
        }
    }
    post_condition(false, "Failed to create SHM File Descriptor");
    return -1;
}

int allocate_shm_file(size_t size) {
    pre_condition(size > 0, "Cannot allocate file with size 0");
    const int shm_fd = create_shm_file();
    check_condition(shm_fd >= 0, "Failed to create valid SHM File Descriptor");
    const int ret = ftruncate(shm_fd, numeric_cast<__off_t>(size));
    post_condition(ret == 0, "Could not resize SHM memory-mapped file");
    return shm_fd;
}

wl_shm_format get_colour_format() {
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
    case (ARGB): return WL_SHM_FORMAT_ARGB8888;
    case (ABGR): return WL_SHM_FORMAT_ABGR8888;
    case (BGRA): return WL_SHM_FORMAT_BGRA8888;
    case (RGBA): return WL_SHM_FORMAT_RGBA8888;
    default:
        throw std::invalid_argument(std::format(
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
        ));
    }
}
} // namespace
#endif

core::window::detail::WaylandWindowImpl::WaylandWindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style) {
    if constexpr (config::EnabledBackends::wayland()) {
        m_wl_shm_format = get_colour_format();
        m_wl_display    = wl_display_connect(nullptr);
        check_ptr(m_wl_display, "Display setup failed");
        m_wl_registry = wl_display_get_registry(m_wl_display);
        check_ptr(m_wl_registry, "Registry setup failed");
        wl_registry_add_listener(m_wl_registry, &m_wl_registry_listener, this);
        check_condition(
            wl_display_roundtrip(m_wl_display) != 0,
            "Display roundtrip failed"
        );
        check_ptr(m_wl_shm, "shm global setup failed");
        check_ptr(m_wl_compositor, "compositor global setup failed");
        check_ptr(m_xdg_wm_base, "xdg_wm_base global setup failed");
        m_wl_surface = wl_compositor_create_surface(m_wl_compositor);
        check_ptr(m_wl_surface, "wl_surface setup failed");
        m_xdg_surface =
            xdg_wm_base_get_xdg_surface(m_xdg_wm_base, m_wl_surface);
        check_ptr(m_xdg_surface, "xdg_surface setup failed");
        m_xdg_toplevel = xdg_surface_get_toplevel(m_xdg_surface);
        check_ptr(m_xdg_toplevel, "xdg_toplevel setup failed");
        xdg_toplevel_add_listener(
            m_xdg_toplevel,
            &m_xdg_toplevel_listener,
            this
        );
        xdg_surface_add_listener(m_xdg_surface, &m_xdg_surface_listener, this);
        wl_surface_commit(m_wl_surface);
        core::log::trace("Surface Committed");
        while ((wl_display_dispatch(m_wl_display) != -1) && (!m_configured)) {
            core::log::error("Wayland display not configured");
        }
        core::log::trace("Display Dispatched");
        xdg_toplevel_set_title(m_xdg_toplevel, get_title().c_str());
        new_buffer();
        restyle();
        wl_surface_attach(m_wl_surface, m_wl_buffer, 0, 0);
        core::log::trace("Surface Attached");
        wl_surface_commit(m_wl_surface);
        core::log::trace("Surface Committed");
        m_wl_callback = wl_surface_frame(m_wl_surface);
        check_ptr(m_wl_callback, "Failed to create callback");
        wl_callback_add_listener(
            m_wl_callback,
            &m_wl_surface_frame_listener,
            this
        );
        core::log::trace("Return from Constructor");
    } else {
        core::condition::unreachable();
    }
}

core::window::detail::WaylandWindowImpl::~WaylandWindowImpl() {
    if constexpr (config::EnabledBackends::wayland()) {
        wl_buffer_destroy(m_wl_buffer);
        wl_surface_destroy(m_wl_surface);
        xdg_surface_destroy(m_xdg_surface);
        xdg_toplevel_destroy(m_xdg_toplevel);
    } else {
        std::unreachable();
    }
}

void core::window::detail::WaylandWindowImpl::draw_line(
    std::span<const Pixel> line,
    Vec2<size_t>           pos
) {
    const std::span line_view{data_row(pos.y), width()};
    log::debug("line.size(): {}", line.size());
    log::debug("line_view.size(): {}", line_view.size());
    const auto size_min = std::min(line.size(), line_view.size());
    for (size_t idx{0}; idx < size_min - 1; ++idx) {
        log::debug("idx: {}", idx);
        const auto& pixel = line[idx];
        log::debug("pixel: {}", pixel.tostring());
        line_view[idx] = pixel;
    }
}

void core::window::detail::WaylandWindowImpl::draw(const drawing::Image& image
) {
    if constexpr (config::EnabledBackends::wayland()) {
        for (size_t col{0}; col < image.height(); ++col) {
            draw_line(image.row(col), {0, col});
        }
    } else {
        core::condition::unreachable();
    }
}

void core::window::detail::WaylandWindowImpl::restyle() {
    restyle(get_style());
}

void core::window::detail::WaylandWindowImpl::restyle(WindowStyle style) {
    if constexpr (config::EnabledBackends::wayland()) {
        switch (style) {
        case WindowStyle::Windowed:
            xdg_toplevel_unset_fullscreen(m_xdg_toplevel);
            xdg_toplevel_unset_maximized(m_xdg_toplevel);
            return;
        case WindowStyle::WindowedFullscreen:
            xdg_toplevel_unset_fullscreen(m_xdg_toplevel);
            xdg_toplevel_set_maximized(m_xdg_toplevel);
            return;
        case WindowStyle::Fullscreen:
            xdg_toplevel_set_fullscreen(m_xdg_toplevel, nullptr);
            return;
        }
    } else {
        core::condition::unreachable();
    }
}

void core::window::detail::WaylandWindowImpl::render_frame() {
    if constexpr (config::EnabledBackends::wayland()) {
        wl_display_dispatch(m_wl_display);
    } else {
        core::condition::unreachable();
    }
}

bool core::window::detail::WaylandWindowImpl::next_frame() {
    if constexpr (config::EnabledBackends::wayland()) {
        if (!should_close()) {
            render_frame();
        }
        return !should_close();
    } else {
        core::condition::unreachable();
    }
}

bool core::window::detail::WaylandWindowImpl::should_close() const {
    if constexpr (config::EnabledBackends::wayland()) {
        return m_should_close;
    } else {
        core::condition::unreachable();
    }
}

void core::window::detail::WaylandWindowImpl::new_buffer() {
    if constexpr (config::EnabledBackends::wayland()) {
        const auto buflen  = safe_mult<size_t>(width(), height());
        const auto bufsize = safe_mult<size_t>(buflen, COLOUR_CHANNELS);
        if (m_shm_fd >= 0) {
            close(m_shm_fd);
        }
        m_shm_fd = allocate_shm_file(bufsize);
        check_condition(m_shm_fd >= 0, "creation of shm buffer file failed");
        m_pixel_buffer = static_cast<Pixel*>(mmap(
            nullptr,
            bufsize,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            m_shm_fd,
            0
        ));
        if (m_pixel_buffer == MAP_FAILED) {
            close(m_shm_fd);
            check_condition(false, "Could not setup shm data");
        }
        m_wl_shm_pool = wl_shm_create_pool(
            m_wl_shm,
            m_shm_fd,
            numeric_cast<int32_t>(bufsize)
        );
        m_wl_buffer = wl_shm_pool_create_buffer(
            m_wl_shm_pool,
            0,
            numeric_cast<int32_t>(width()),
            numeric_cast<int32_t>(height()),
            safe_mult<int32_t>(width(), COLOUR_CHANNELS),
            m_wl_shm_format
        );
        if (m_wl_shm_pool != nullptr) {
            wl_shm_pool_destroy(m_wl_shm_pool);
        }
        check_ptr(m_wl_buffer, "Failed to create buffer");
    } else {
        core::condition::unreachable();
    }
}
