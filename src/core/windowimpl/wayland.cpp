#include "core/windowimpl/wayland.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/math.h"
#include <algorithm>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <random>
#include <sys/mman.h>
#include <unistd.h>
using core::condition::check_condition;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;

namespace core::window::wayland {
wl_state_t wayland_state; // NOLINT: -avoid-non-const-global-variables
}

namespace {
constexpr std::string_view alnum =
    "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

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
} // namespace

struct wl_buffer* core::window::wayland::create_buffer(
    const size_t& width,
    const size_t& height,
    const size_t& buffer_size
) {
    const auto size   = numeric_cast<int32_t>(buffer_size * COLOUR_CHANNELS);
    const int  shm_fd = allocate_shm_file(size);
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
        numeric_cast<int32_t>(size * N_BUFFERS)
    );
    struct wl_buffer* buffer = wl_shm_pool_create_buffer(
        pool,
        0,
        numeric_cast<int32_t>(width),
        numeric_cast<int32_t>(height),
        numeric_cast<int32_t>(width * COLOUR_CHANNELS),
        WL_SHM_FORMAT_ARGB8888
    );
    wl_shm_pool_destroy(pool);
    close(shm_fd);
    check_condition(buffer != nullptr, "Null buffer");
    return buffer;
}

namespace core::window::wayland {

void init_window(
    const size_t&      width,
    const size_t&      height,
    const size_t&      buffer_size,
    const std::string& title
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
        &registry_listener,
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
        &xdg_surface_listener,
        nullptr
    );
    wl_surface_commit(wayland_state.m_surface);
    log::debug("Surface Committed");
    while (wl_display_dispatch(wayland_state.m_display) != -1
           && !wayland_state.m_configured) {
        log::error("Wayland display not configured");
    }
    log::debug("Display dispatched");
    core::log::debug(
        std::format("wayland_state.m_shm: {}", size_t(wayland_state.m_shm))
    );
    wayland_state.m_buffer =
        core::window::wayland::create_buffer(width, height, buffer_size);
    check_condition(
        wayland_state.m_buffer != nullptr,
        "Failed to setup buffer"
    );
    wl_surface_attach(wayland_state.m_surface, wayland_state.m_buffer, 0, 0);
    wl_surface_commit(wayland_state.m_surface);
    xdg_toplevel_set_title(wayland_state.m_xdg_toplevel, title.c_str());
    wayland_state.m_running = true;
}

void destroy_window() {
    xdg_toplevel_destroy(wayland_state.m_xdg_toplevel);
    xdg_surface_destroy(wayland_state.m_xdg_surface);
    wl_surface_destroy(wayland_state.m_surface);
    wl_buffer_destroy(wayland_state.m_buffer);
}

void render_frame() {
    // handle bad dispatch, set to close
    if (wl_display_dispatch(wayland_state.m_display) == -1) {
        log::error("Bad display dispatch");
        wayland_state.m_running = false;
        return;
    }
    using core::window::wayland::wayland_state;
    memset(
        wayland_state.m_shm_data,
        0xFFU,
        (core::DEFAULT_WINDOW_WIDTH * core::DEFAULT_WINDOW_HEIGHT * 4)
    );
}

} // namespace core::window::wayland
