#include "raygame/core/window/detail/wayland.h"
#include "raygame/core/condition.h"
#include "raygame/core/drawing/pixel.h"
#include "raygame/core/logger.h"
#include "raygame/core/math/random.h"
#include <algorithm>
#include <cstdlib>
#include <fcntl.h>
#include <string_view>
#include <sys/mman.h>
#include <unistd.h>
#include <utility>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>
#include <xkbcommon/xkbcommon.h>

#if !defined(NDEBUG)
#    define PRINT_KEY
#endif

namespace {
using core::condition::check_condition;
using core::condition::check_ptr;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;
using core::math::safe_mult;

constexpr size_t COLOUR_CHANNELS = 4;

constexpr std::string_view alnum = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

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
        const std::string name("/wl_shm-" + random_string(RAND_LEN));
        const int         shm_fd = shm_open(name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0600);
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

[[maybe_unused]]
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
    case (ARGB): core::log::debug("Colour Format: ARGB"); return WL_SHM_FORMAT_ARGB8888;
    case (ABGR): core::log::debug("Colour Format: ABGR"); return WL_SHM_FORMAT_ABGR8888;
    case (BGRA): core::log::debug("Colour Format: BGRA"); return WL_SHM_FORMAT_BGRA8888;
    case (RGBA): core::log::debug("Colour Format: RGBA"); return WL_SHM_FORMAT_RGBA8888;
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
WaylandWindowImpl::WaylandWindowImpl(Vec2<size_t> size, std::string title, WindowStyle style)
    : WindowImpl(size, std::move(title), style) {
    if constexpr (config::EnabledBackends::wayland()) {
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
        xdg_toplevel_set_title(m_xdg_toplevel, get_title().c_str());
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

WaylandWindowImpl::~WaylandWindowImpl() {
    m_buffer_width  = 0;
    m_buffer_height = 0;
    xdg_toplevel_destroy(m_xdg_toplevel);
    xdg_surface_destroy(m_xdg_surface);
    wl_surface_destroy(m_wl_surface);
}

void WaylandWindowImpl::draw(const drawing::ImageView& image) {
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
            m_pixbuf[row, col] = image[therow, thecol];
        }
    }
    log::debug("Drawn: {} rows, {} cols", row - row_left, col - col_top);
}

void WaylandWindowImpl::restyle() {
    restyle(get_style());
}

void WaylandWindowImpl::restyle(WindowStyle style) {
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
}

void WaylandWindowImpl::render_frame() {
    wl_surface_commit(m_wl_surface);
    log::trace("Surface Committed");
    wl_display_dispatch(m_wl_display);
}

bool WaylandWindowImpl::next_frame() {
    if constexpr (TIME_FRAMES) {
        frame_time_start();
    }
    if (!should_close()) {
        render_frame();
    }
    if constexpr (TIME_FRAMES) {
        frame_time_end();
    }
    return !should_close();
}

bool WaylandWindowImpl::should_close() const {
    return m_should_close;
}

void WaylandWindowImpl::new_buffer() {
    const auto bufwidth  = width();
    const auto bufheight = height();
    const auto bufstride = safe_mult<size_t>(bufwidth, COLOUR_CHANNELS);
    const auto buflen    = safe_mult<size_t>(bufstride, bufheight);
    log::debug("Requesting buffer with size: {}, {}", bufwidth, bufheight);
    log::trace("buflen: {}", buflen);
    if (m_shm_fd >= 0) {
        close(m_shm_fd);
    }
    m_shm_fd = allocate_shm_file(buflen);
    check_condition(m_shm_fd >= 0, "creation of shm buffer file failed");
    auto* const pixbuf =
        static_cast<Pixel*>(mmap(nullptr, buflen, PROT_READ | PROT_WRITE, MAP_SHARED, m_shm_fd, 0));
    if (pixbuf == MAP_FAILED) {
        close(m_shm_fd);
        check_condition(false, "Could not setup shm data");
    }
    m_pixbuf      = {pixbuf, std::extents(bufwidth, bufheight)};
    m_wl_shm_pool = wl_shm_create_pool(m_wl_shm, m_shm_fd, numeric_cast<int32_t>(buflen));
    m_wl_buffer   = wl_shm_pool_create_buffer(
        m_wl_shm_pool,
        0,
        numeric_cast<int32_t>(bufwidth),
        numeric_cast<int32_t>(bufheight),
        numeric_cast<int32_t>(bufstride),
        m_wl_shm_format
    );
    m_buffer_width  = bufwidth;
    m_buffer_height = bufheight;
    check_ptr(m_wl_buffer, "Failed to create buffer");
    wl_surface_attach(m_wl_surface, m_wl_buffer, 0, 0);
    log::trace("Surface Attached");
    if (m_wl_shm_pool != nullptr) {
        wl_shm_pool_destroy(m_wl_shm_pool);
    }
    for (size_t idx{0}; idx <= bufheight; ++idx) {
        for (size_t jdx{0}; jdx <= bufwidth; ++jdx) {
            m_pixbuf[idx, jdx] = colour::BLACK;
        }
    }
}

// NOLINTBEGIN(*-easily-swappable-parameters)
void KeyboardState::update_mask(
    uint32_t mods_depressed,
    uint32_t mods_latched,
    uint32_t mods_locked,
    uint32_t group
) {
    log::trace("update_mask: {}, {}, {}, {}", mods_depressed, mods_latched, mods_locked, group);
    xkb_state_update_mask(
        m_xkb_state.get(),
        mods_depressed,
        mods_latched,
        mods_locked,
        0,
        0,
        group
    );
    log::trace("mask updated");
}

void KeyboardState::new_from_string(const char* str) {
    log::trace("new_from_string start");
    m_xkb_keymap.reset(xkb_keymap_new_from_string(
        m_xkb_context.get(),
        str,
        XKB_KEYMAP_FORMAT_TEXT_V1,
        XKB_KEYMAP_COMPILE_NO_FLAGS
    ));
    log::trace("new_from_string done");
}

void KeyboardState::event(const uint32_t& key, const uint32_t& state) {
    log::debug("event: key({}), state({})", key, state);
#if defined(PRINT_KEY)
    constexpr uint32_t        KEY_OFFSET{8};
    const uint32_t            keycode{key + KEY_OFFSET};
    const xkb_keysym_t        sym{xkb_state_key_get_one_sym(m_xkb_state.get(), keycode)};
    constexpr size_t          BUFSIZE{128};
    std::array<char, BUFSIZE> buf{0};
    xkb_keysym_get_name(sym, buf.data(), sizeof(buf));
    const char* action{state == WL_KEYBOARD_KEY_STATE_PRESSED ? "press" : "release"};
    log::debug("key {}: sym: {} ({}), ", action, std::string_view(buf), sym);
#endif
}

// NOLINTEND(*-easily-swappable-parameters)

} // namespace core::window::detail
