#include "core/windowimpl/wayland.h"
#include "core/colours.h"
#include "core/condition.h"
#include "core/logger.h"
#include "core/math.h"
#include "core/window.h"
#include <cstring>
#include <fcntl.h>
#include <format>
#include <linux/input-event-codes.h>
#include <random>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>
#include <wayland-client-protocol.h>

using core::condition::check_condition;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;

namespace {

constexpr size_t           COLOUR_CHANNELS = 4;
constexpr std::string_view alnum =
    "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

struct wl_state_t {
    struct wl_buffer*     m_buffer;
    struct wl_compositor* m_compositor;
    struct wl_display*    m_display;
    struct wl_keyboard*   m_wl_keyboard;
    struct wl_pointer*    m_wl_pointer;
    struct wl_registry*   m_registry;
    struct wl_seat*       m_wl_seat;
    struct wl_shm*        m_shm;
    struct wl_surface*    m_surface;
    struct wl_touch*      m_wl_touch;
    struct xdg_surface*   m_xdg_surface;
    struct xdg_toplevel*  m_xdg_toplevel;
    struct xdg_wm_base*   m_xdg_wm_base;
    void*                 m_shm_data;
    bool                  m_configured;
    bool                  m_running;
};

wl_state_t wayland_state;

std::string random_string(
    const size_t&      length,
    const std::string& valid_chars = alnum.data()
) {
    std::uniform_int_distribution<size_t> dist{0, valid_chars.length() - 1};
    std::mt19937_64                       gen{std::random_device()()};
    std::string                           ret;
    std::generate_n(std::back_inserter(ret), length, [&] {
        return valid_chars[dist(gen)];
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

void rg_xdg_wm_base_handle_ping(
    [[maybe_unused]] void* data,
    struct xdg_wm_base*    xdg_wm_base,
    uint32_t               serial
) {
    xdg_wm_base_pong(xdg_wm_base, serial);
}

const struct xdg_wm_base_listener rg_xdg_wm_base_listener = {
    .ping = rg_xdg_wm_base_handle_ping,
};

void rg_xdg_surface_handle_configure(
    [[maybe_unused]] void* data,
    struct xdg_surface*    xdg_surface,
    uint32_t               serial
) {
    xdg_surface_ack_configure(xdg_surface, serial);
    if (wayland_state.m_configured) {
        wl_surface_commit(wayland_state.m_surface);
    }
    wayland_state.m_configured = true;
}

const struct xdg_surface_listener rg_xdg_surface_listener = {
    .configure = rg_xdg_surface_handle_configure,
};

void rg_xdg_toplevel_handle_configure(
    [[maybe_unused]] void*                data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
    [[maybe_unused]] int32_t              width,
    [[maybe_unused]] int32_t              height,
    [[maybe_unused]] struct wl_array*     states
) {}

void rg_xdg_toplevel_handle_close(
    [[maybe_unused]] void*                data,
    [[maybe_unused]] struct xdg_toplevel* xdg_toplevel
) {
    wayland_state.m_running = false;
}

[[maybe_unused]]
const struct xdg_toplevel_listener rg_xdg_toplevel_listener = {
    .configure        = rg_xdg_toplevel_handle_configure,
    .close            = rg_xdg_toplevel_handle_close,
    .configure_bounds = nullptr,
    .wm_capabilities  = nullptr,
}; // namespace

void rg_wl_pointer_handle_enter(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t           serial,
    [[maybe_unused]] struct wl_surface* surface,
    [[maybe_unused]] wl_fixed_t         surface_x,
    [[maybe_unused]] wl_fixed_t         surface_y
) {}

void rg_wl_pointer_handle_leave(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t           serial,
    [[maybe_unused]] struct wl_surface* surface
) {}

void rg_wl_pointer_handle_motion(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t           time,
    [[maybe_unused]] wl_fixed_t         surface_x,
    [[maybe_unused]] wl_fixed_t         surface_y
) {}

void rg_wl_pointer_handle_button(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* pointer,
    uint32_t                            serial,
    [[maybe_unused]] uint32_t           time,
    uint32_t                            button,
    uint32_t                            state
) {
    auto* seat = static_cast<struct wl_seat*>(data);
    if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED) {
        xdg_toplevel_move(wayland_state.m_xdg_toplevel, seat, serial);
    }
}

void rg_wl_pointer_handle_axis(
    [[maybe_unused]] void*              data,
    [[maybe_unused]] struct wl_pointer* wl_pointer,
    [[maybe_unused]] uint32_t           time,
    [[maybe_unused]] uint32_t           axis,
    [[maybe_unused]] wl_fixed_t         value
) {}

const struct wl_pointer_listener rg_wl_pointer_listener = {
    .enter  = rg_wl_pointer_handle_enter,
    .leave  = rg_wl_pointer_handle_leave,
    .motion = rg_wl_pointer_handle_motion,
    .button = rg_wl_pointer_handle_button,
    .axis   = rg_wl_pointer_handle_axis,

    .frame                   = nullptr,
    .axis_source             = nullptr,
    .axis_stop               = nullptr,
    .axis_discrete           = nullptr,
    .axis_value120           = nullptr,
    .axis_relative_direction = nullptr,
};

void rg_wl_seat_handle_capabilities(
    [[maybe_unused]] void*           data,
    [[maybe_unused]] struct wl_seat* seat,
    [[maybe_unused]] uint32_t        capabilities
) {
    // If the wl_seat has the pointer capability, start listening to pointer
    // events
    if ((capabilities & WL_SEAT_CAPABILITY_POINTER) != 0U) {
        struct wl_pointer* pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(pointer, &rg_wl_pointer_listener, seat);
    }
}

const struct wl_seat_listener rg_wl_seat_listener = {
    .capabilities = rg_wl_seat_handle_capabilities,
    .name         = nullptr,
};

void rg_wl_handle_global(
    [[maybe_unused]] void*               data,
    [[maybe_unused]] struct wl_registry* registry,
    [[maybe_unused]] uint32_t            name,
    [[maybe_unused]] const char*         interface,
    [[maybe_unused]] uint32_t            version
) {
    if (strcmp(interface, wl_shm_interface.name) == 0) {
        core::log::debug(std::format("{}", interface));
        wayland_state.m_shm = static_cast<struct wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, 1)
        );
    } else if (strcmp(interface, wl_seat_interface.name) == 0) {
        core::log::debug(std::format("{}", interface));
        auto* seat = static_cast<struct wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface, 1)
        );
        wl_seat_add_listener(seat, &rg_wl_seat_listener, nullptr);
    } else if (strcmp(interface, wl_compositor_interface.name) == 0) {
        core::log::debug(std::format("{}", interface));
        wayland_state.m_compositor = static_cast<struct wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, 1)
        );
    } else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
        core::log::debug(std::format("{}", interface));
        wayland_state.m_xdg_wm_base = static_cast<struct xdg_wm_base*>(
            wl_registry_bind(registry, name, &xdg_wm_base_interface, 1)
        );
        xdg_wm_base_add_listener(
            wayland_state.m_xdg_wm_base,
            &rg_xdg_wm_base_listener,
            nullptr
        );
    } else if (strcmp(interface, wl_seat_interface.name) == 0) {
        core::log::debug(std::format("{}", interface));
        wayland_state.m_wl_seat = static_cast<struct wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface, 7)
        );
        wl_seat_add_listener(
            wayland_state.m_wl_seat,
            &rg_wl_seat_listener,
            nullptr
        );
    } else {
        core::log::trace(std::format("Unhandled: {}", interface));
    }
}

void rg_wl_handle_global_remove(
    [[maybe_unused]] void*               data,
    [[maybe_unused]] struct wl_registry* registry,
    [[maybe_unused]] uint32_t            name
) {}

const struct wl_registry_listener rg_wl_registry_listener = {
    .global        = rg_wl_handle_global,
    .global_remove = rg_wl_handle_global_remove,
};

constexpr wl_shm_format get_colour_format() {
    using core::colour::rgba;
    using std::bit_cast;
    constexpr auto colourval =
        rgba(0b00000000, 0b11111111, 0b00111100, 0b11000011);
    switch (bit_cast<uint32_t>(colourval)) {
    case (0b11000011'00000000'11111111'00111100):
        return WL_SHM_FORMAT_ARGB8888;
    case (0b11000011'00111100'11111111'00000000):
        return WL_SHM_FORMAT_ABGR8888;
    case (0b00111100'11111111'00000000'11000011):
        return WL_SHM_FORMAT_BGRA8888;
    case (0b00000000'11111111'00111100'11000011):
        return WL_SHM_FORMAT_RGBA8888;
    default:
        throw std::invalid_argument(std::format(
            "Could not determine colour format:\n"
            "functdef: {:0>32b}\n"
            "RGBA DEF: {:0>32b}\n"
            "RGBA set: {:0>32b}{:0>32b}{:0>32b}{:0>32b}\n"
            "BYTE NO:  00000000111111112222222233333333\n",
            bit_cast<uint32_t>(colourval),
            (0b00000000'11111111'00111100'11000011),
            colourval.m_alpha,
            colourval.m_blue,
            colourval.m_green,
            colourval.m_red
        ));
    }
}

} // namespace

struct wl_buffer* core::window::wayland::create_buffer(
    const size_t& width,
    const size_t& height
) {
    return create_buffer(
        width,
        height,
        core::math::numeric_cast<size_t>(width * height)
    );
};

struct wl_buffer* core::window::wayland::create_buffer(
    const size_t& width,
    const size_t& height,
    const size_t& buffer_size
) {
    const size_t size   = numeric_cast<size_t>(buffer_size * COLOUR_CHANNELS);
    const int    shm_fd = allocate_shm_file(size);
    check_condition(shm_fd >= 0, "creation of shm buffer file failed");
    wayland_state.m_shm_data =
        mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (wayland_state.m_shm_data == MAP_FAILED) {
        close(shm_fd);
        check_condition(false, "Could not setup shm data");
    }
    struct wl_shm_pool* pool = wl_shm_create_pool(
        wayland_state.m_shm,
        shm_fd,
        numeric_cast<int32_t>(size)
    );
    struct wl_buffer* buffer = wl_shm_pool_create_buffer(
        pool,
        0,
        numeric_cast<int32_t>(width),
        numeric_cast<int32_t>(height),
        numeric_cast<int32_t>(width * COLOUR_CHANNELS),
        get_colour_format()
    );
    wl_shm_pool_destroy(pool);
    close(shm_fd);
    check_condition(buffer != nullptr, "Null buffer");
    return buffer;
}

void core::window::wayland::init_window(
    const size_t&            width,
    const size_t&            height,
    const size_t&            buffer_size,
    const std::string&       title,
    const core::WindowStyle& style
) {
    wayland_state.m_display = wl_display_connect(nullptr);
    check_condition(wayland_state.m_display != nullptr, "Display setup failed");
    wayland_state.m_registry = wl_display_get_registry(wayland_state.m_display);
    log::debug("Registry setup");
    check_condition(
        wayland_state.m_registry != nullptr,
        "Registry setup failed"
    );
    wl_registry_add_listener(
        wayland_state.m_registry,
        &rg_wl_registry_listener,
        nullptr
    );
    log::debug("Display roundtrip");
    check_condition(
        wl_display_roundtrip(wayland_state.m_display) != 0,
        "Display roundtrip failed"
    );
    check_condition(
        wayland_state.m_shm != nullptr,
        "shm global not setup correctly"
    );
    check_condition(
        wayland_state.m_compositor != nullptr,
        "compositor global not setup correctly"
    );
    check_condition(
        wayland_state.m_xdg_wm_base != nullptr,
        "xdg_wm_base global not setup correctly"
    );
    wayland_state.m_surface =
        wl_compositor_create_surface(wayland_state.m_compositor);
    log::debug("Surface created");
    wayland_state.m_xdg_surface = xdg_wm_base_get_xdg_surface(
        wayland_state.m_xdg_wm_base,
        wayland_state.m_surface
    );
    wayland_state.m_xdg_toplevel =
        xdg_surface_get_toplevel(wayland_state.m_xdg_surface);
    log::debug("Toplevel Created");
    xdg_surface_add_listener(
        wayland_state.m_xdg_surface,
        &rg_xdg_surface_listener,
        nullptr
    );
    wl_surface_commit(wayland_state.m_surface);
    log::debug("Surface Committed");
    while (wl_display_dispatch(wayland_state.m_display) != -1
           && !wayland_state.m_configured) {
        log::error("Wayland display not configured");
    }
    log::debug("Display dispatched");
    wayland_state.m_buffer =
        core::window::wayland::create_buffer(width, height, buffer_size);
    check_condition(
        wayland_state.m_buffer != nullptr,
        "Failed to setup buffer"
    );
    xdg_toplevel_set_title(wayland_state.m_xdg_toplevel, title.c_str());
    wl_surface_attach(wayland_state.m_surface, wayland_state.m_buffer, 0, 0);
    wl_surface_commit(wayland_state.m_surface);
    core::log::debug("First frame committed");
    if (style == WindowStyle::Fullscreen) {
        xdg_toplevel_set_fullscreen(wayland_state.m_xdg_toplevel, nullptr);
    } else if (style == WindowStyle::WindowedFullscreen) {
        xdg_toplevel_unset_fullscreen(wayland_state.m_xdg_toplevel);
        xdg_toplevel_set_maximized(wayland_state.m_xdg_toplevel);
    } else if (style == WindowStyle::Windowed) {
        xdg_toplevel_unset_fullscreen(wayland_state.m_xdg_toplevel);
        xdg_toplevel_unset_maximized(wayland_state.m_xdg_toplevel);
    }
    wayland_state.m_running = true;
}

void core::window::wayland::destroy_window() {
    xdg_toplevel_destroy(wayland_state.m_xdg_toplevel);
    xdg_surface_destroy(wayland_state.m_xdg_surface);
    wl_surface_destroy(wayland_state.m_surface);
    wl_buffer_destroy(wayland_state.m_buffer);
}

void core::window::wayland::render_frame(
    const size_t& width,
    const size_t& height
) {
    // handle bad dispatch, set to close
    if (wl_display_dispatch(wayland_state.m_display) == -1) {
        log::error("Bad display dispatch");
        wayland_state.m_running = false;
        return;
    }
    wl_surface_damage(
        wayland_state.m_surface,
        0,
        0,
        numeric_cast<int32_t>(width),
        numeric_cast<int32_t>(height)
    );
    wl_surface_attach(wayland_state.m_surface, wayland_state.m_buffer, 0, 0);
    wl_surface_commit(wayland_state.m_surface);
}

bool core::window::wayland::should_close() {
    return !wayland_state.m_running;
}

static_assert(core::IsWindow<core::window::wayland::WaylandWindow>);
