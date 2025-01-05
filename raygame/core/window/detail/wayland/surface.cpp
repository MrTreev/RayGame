#include "raygame/core/window/detail/wayland/surface.h"
#include "raygame/core/condition.h"
#include "raygame/core/drawing/colour.h"
#include "raygame/core/math/numeric_cast.h"
#include "raygame/core/math/random.h"
#include <algorithm>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

namespace {
using core::condition::check_condition;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;

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

namespace core::window::detail {
WaylandSurface::WaylandSurface()
    : m_wl_shm_format(get_colour_format()) {}

WaylandSurface::~WaylandSurface() {
    wl_buffer_destroy(m_wl_buffer);
    wl_surface_destroy(m_wl_surface);
    xdg_surface_destroy(m_xdg_surface);
}

const wl_callback_listener WaylandSurface::m_callback_listener{
    .done = done,
};
const xdg_surface_listener WaylandSurface::m_xdg_listener{
    .configure = configure,
};

void WaylandSurface::new_buffer() {
    const auto buflen  = math::safe_mult<size_t>(m_size.x, m_size.y);
    const auto bufsize = math::safe_mult<size_t>(buflen, COLOUR_CHANNELS);
    if (m_wl_shm_pool != nullptr) {
        wl_shm_pool_destroy(m_wl_shm_pool);
    }
    if (m_shm_fd >= 0) {
        close(m_shm_fd);
    }
    m_shm_fd = allocate_shm_file(bufsize);
    condition::check_condition(
        m_shm_fd >= 0,
        "creation of shm buffer file failed"
    );
    m_pixel_buffer = static_cast<uint8_t*>(
        mmap(nullptr, bufsize, PROT_READ | PROT_WRITE, MAP_SHARED, m_shm_fd, 0)
    );
    if (m_pixel_buffer == MAP_FAILED) {
        close(m_shm_fd);
        condition::check_condition(false, "Could not setup shm data");
    }
    m_wl_shm_pool = wl_shm_create_pool(
        m_wl_shm,
        m_shm_fd,
        math::numeric_cast<int32_t>(bufsize)
    );
    m_wl_buffer = wl_shm_pool_create_buffer(
        m_wl_shm_pool,
        0,
        math::numeric_cast<int32_t>(m_size.x),
        math::numeric_cast<int32_t>(m_size.y),
        math::safe_mult<int32_t>(m_size.x, COLOUR_CHANNELS),
        m_wl_shm_format
    );
    condition::check_ptr(m_wl_buffer, "Failed to create buffer");
}

void WaylandSurface::done(void* data, wl_callback* wl_callback, uint32_t time) {
    auto* this_impl = static_cast<WaylandSurface*>(data);
    wl_callback_destroy(wl_callback);
    wl_callback = wl_surface_frame(this_impl->m_wl_surface);
    wl_callback_add_listener(wl_callback, &m_callback_listener, this_impl);
    this_impl->new_buffer();
    wl_surface_attach(this_impl->m_wl_surface, this_impl->m_wl_buffer, 0, 0);
    wl_surface_damage_buffer(
        this_impl->m_wl_surface,
        0,
        0,
        math::numeric_cast<int32_t>(this_impl->m_size.x),
        math::numeric_cast<int32_t>(this_impl->m_size.y)
    );
    wl_surface_commit(this_impl->m_wl_surface);
    this_impl->m_last_frame = time;
}

} // namespace core::window::detail
