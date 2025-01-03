#include "raygame/core/window/detail/wayland.h"
#include "raygame/core/drawing/colour.h"
#include <cstring>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <unistd.h>

namespace {
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

core::window::detail::WaylandWindowImpl::WaylandWindowImpl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : WindowImpl(size, std::move(title), style)
    , m_shm_format(get_colour_format()) {}

core::window::detail::WaylandWindowImpl::~WaylandWindowImpl() = default;

void core::window::detail::WaylandWindowImpl::draw(const drawing::Image& image
) {
    std::ignore = image;
}

void core::window::detail::WaylandWindowImpl::restyle(WindowStyle style) {
    std::ignore = style;
}

void core::window::detail::WaylandWindowImpl::render_frame() {}

bool core::window::detail::WaylandWindowImpl::next_frame() {
    return false;
}

bool core::window::detail::WaylandWindowImpl::should_close() const {
    return true;
}
