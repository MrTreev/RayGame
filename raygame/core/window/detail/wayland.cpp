#include "raygame/core/window/wayland.h"
#include "raygame/core/condition.h"
#include "raygame/core/drawing/colour.h"
#include "raygame/core/logger.h"
#include "raygame/core/math/arithmetic.h"
#include "raygame/core/math/numeric_cast.h"
#include "raygame/core/math/random.h"
#include <algorithm>
#include <cstring>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include <xdg-shell-client-protocol.h>
#include <xkbcommon/xkbcommon.h>

using core::condition::check_condition;
using core::condition::check_ptr;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;
using core::math::safe_mult;

namespace {

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

constexpr size_t COLOUR_CHANNELS = 4;

} // namespace

core::window::detail::WaylandImpl::keyboard_state::keyboard_state()
    : m_xkb_context(xkb_context_new(XKB_CONTEXT_NO_FLAGS)) {}

core::window::detail::WaylandImpl::keyboard_state::~keyboard_state() {
    xkb_context_unref(m_xkb_context);
    m_xkb_context = nullptr;
}

core::window::detail::WaylandImpl::WaylandImpl(WaylandWindow* base)
    : m_base(base)
    , m_wl_shm_format(get_colour_format())
    , m_size(base->win_size()) {
    // NOLINTNEXTLINE(*-prefer-member-initializer)
    m_wl_display = wl_display_connect(nullptr);
    check_ptr(m_wl_display, "Display setup failed");
    // NOLINTNEXTLINE(*-prefer-member-initializer)
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
    // NOLINTNEXTLINE(*-prefer-member-initializer)
    m_wl_surface = wl_compositor_create_surface(m_wl_compositor);
    check_ptr(m_wl_surface, "wl_surface setup failed");
    m_xdg_surface = xdg_wm_base_get_xdg_surface(m_xdg_wm_base, m_wl_surface);
    check_ptr(m_xdg_surface, "xdg_surface setup failed");
    // NOLINTNEXTLINE(*-prefer-member-initializer)
    m_xdg_toplevel = xdg_surface_get_toplevel(m_xdg_surface);
    check_ptr(m_xdg_toplevel, "xdg_toplevel setup failed");
    xdg_toplevel_add_listener(m_xdg_toplevel, &m_xdg_toplevel_listener, this);
    xdg_surface_add_listener(m_xdg_surface, &m_xdg_surface_listener, this);
    wl_surface_commit(m_wl_surface);
    core::log::trace("Surface Committed");
    while ((wl_display_dispatch(m_wl_display) != -1) && (!m_configured)) {
        core::log::error("Wayland display not configured");
    }
    core::log::trace("Display Dispatched");
    xdg_toplevel_set_title(m_xdg_toplevel, base->title().c_str());
    new_buffer(m_size);
    set_style(base->style());
    wl_surface_attach(m_wl_surface, m_wl_buffer, 0, 0);
    core::log::trace("Surface Attached");
    wl_surface_commit(m_wl_surface);
    core::log::trace("Surface Committed");
    m_wl_callback = wl_surface_frame(m_wl_surface);
    check_ptr(m_wl_callback, "Failed to create callback");
    wl_callback_add_listener(m_wl_callback, &m_wl_surface_frame_listener, this);
    core::log::trace("Return from Constructor");
}

core::window::detail::WaylandImpl::~WaylandImpl() {
    wl_buffer_destroy(m_wl_buffer);
    wl_surface_destroy(m_wl_surface);
    xdg_surface_destroy(m_xdg_surface);
    xdg_toplevel_destroy(m_xdg_toplevel);
}

void core::window::detail::WaylandImpl::new_buffer(core::Vec2<size_t> size) {
    const auto buflen  = safe_mult<size_t>(size.x, size.y);
    const auto bufsize = safe_mult<size_t>(buflen, COLOUR_CHANNELS);
    if (m_wl_shm_pool != nullptr) {
        wl_shm_pool_destroy(m_wl_shm_pool);
    }
    if (m_shm_fd >= 0) {
        close(m_shm_fd);
    }
    m_shm_fd = allocate_shm_file(bufsize);
    check_condition(m_shm_fd >= 0, "creation of shm buffer file failed");
    m_pixel_buffer = static_cast<uint8_t*>(
        mmap(nullptr, bufsize, PROT_READ | PROT_WRITE, MAP_SHARED, m_shm_fd, 0)
    );
    if (m_pixel_buffer == MAP_FAILED) {
        close(m_shm_fd);
        check_condition(false, "Could not setup shm data");
    }
    m_wl_shm_pool =
        wl_shm_create_pool(m_wl_shm, m_shm_fd, numeric_cast<int32_t>(bufsize));
    m_wl_buffer = wl_shm_pool_create_buffer(
        m_wl_shm_pool,
        0,
        numeric_cast<int32_t>(size.x),
        numeric_cast<int32_t>(size.y),
        safe_mult<int32_t>(size.x, COLOUR_CHANNELS),
        m_wl_shm_format
    );
    check_ptr(m_wl_buffer, "Failed to create buffer");
}

void core::window::detail::WaylandImpl::render_frame() {
    wl_display_dispatch(m_wl_display);
}

void core::window::detail::WaylandImpl::set_style(
    core::window::WindowStyle style
) {
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
}
