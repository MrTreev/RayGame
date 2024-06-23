#include "core/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/config.h"
#include "core/logger.h"
#include "core/types.h"
#include <random>

namespace {
constexpr size_t COLOUR_CHANNELS = 4;
constexpr size_t N_BUFFERS       = 2;
} // namespace

#if defined(RAYGAME_GUI_WAYLAND)
#    include <cstring>
#    include <fcntl.h>
#    include <sys/mman.h>
#    include <wayland-client.h>
#endif

namespace {

void registry_handle_global(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name,
    const char*         interface,
    uint32_t            version
);
void registry_handle_global_remove(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name
);
} // namespace

#if defined(RAYGAME_GUI_WAYLAND)
struct core::WaylandWinState {
    std::string title;
    size_t      width       = 0;
    size_t      height      = 0;
    size_t      buffer_size = 0;
    int         shm_fd      = 0;

    const struct wl_registry_listener registry_listener = {
        .global        = registry_handle_global,
        .global_remove = registry_handle_global_remove,
    };

    struct wl_compositor* compositor = nullptr;
    struct wl_display*    display    = nullptr;
    struct wl_registry*   registry   = nullptr;
    struct wl_shm*        shm        = nullptr;
    struct wl_shm_pool*   shm_pool   = nullptr;
    struct wl_surface*    surface    = nullptr;
};

namespace {

#    define RG_PRINT_REG_INFO                                                  \
        core::log::debug(std::format(                                          \
            "interface: '{}', version: '{}', name: '{}'",                      \
            interface,                                                         \
            version,                                                           \
            name                                                               \
        ));

void registry_handle_global(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name,
    const char*         interface,
    uint32_t            version
) {
    auto* state = static_cast<core::WaylandWinState*>(data);
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        RG_PRINT_REG_INFO
        state->compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, 4)
        );
        state->surface = wl_compositor_create_surface(state->compositor);
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        RG_PRINT_REG_INFO
        state->shm = static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, 1)
        );
    }
}

#    undef RG_PRINT_REG_INFO

void registry_handle_global_remove(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name
) {
    // Left Blank
}

constexpr std::string_view alnum =
    "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

std::string random_string(
    const size_t&      length,
    const std::string& valid_chars = alnum.data()
) {
    std::uniform_int_distribution<size_t> dist{0, valid_chars.length() - 1};

    std::mt19937_64 gen{std::random_device()()};
    std::string     ret;
    std::generate_n(std::back_inserter(ret), length, [&] {
        return valid_chars[dist(gen)];
    });
    return ret;
}

int create_shm_file() {
    for (int retries = 100; retries > 0; --retries) {
        std::string name("/wl_shm-");
        name.append(random_string(6));
        const int shm_fd =
            shm_open(name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0600);
        if (shm_fd >= 0) {
            shm_unlink(name.c_str());
            return shm_fd;
        }
    }
    core::condition::post_condition(
        false,
        "Failed to create SHM File Descriptor"
    );
    return -1;
}

int allocate_shm_file(size_t size) {
    core::condition::pre_condition(
        size > 0,
        "Cannot allocate file with size 0"
    );
    const int shm_fd = create_shm_file();
    core::condition::check_condition(
        shm_fd >= 0,
        "Failed to create valid SHM File Descriptor"
    );
    const int ret = ftruncate(shm_fd, size);
    core::condition::post_condition(
        ret >= 0,
        "Could not resize SHM memory-mapped file"
    );
    return shm_fd;
}

} // namespace
#endif

core::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& title,
    const WindowStyle& style
)
    : _win_state(std::make_unique<core::WaylandWinState>()) {
    core::log::debug("Window attempt");
    _win_state->title       = title;
    _win_state->height      = height;
    _win_state->width       = width;
    _win_state->buffer_size = width * height;
#if defined(RAYGAME_GUI_WAYLAND)

    _win_state->display = wl_display_connect(nullptr);
    core::condition::check_condition(
        _win_state->display != nullptr,
        "Unable to create Wayland display"
    );

    _win_state->registry = wl_display_get_registry(_win_state->display);
    core::condition::check_condition(
        _win_state->display != nullptr,
        "Unable to create Wayland registry"
    );

    wl_registry_add_listener(
        _win_state->registry,
        &_win_state->registry_listener,
        &_win_state
    );

    const size_t stride     = width * COLOUR_CHANNELS;
    _win_state->buffer_size = height * stride;
    const size_t pool_size  = _win_state->buffer_size * N_BUFFERS;
    const int    shm_fd     = allocate_shm_file(pool_size);

    auto* pool_data = static_cast<uint8_t*>(
        mmap(nullptr, pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
    );
    struct wl_shm_pool* pool = wl_shm_create_pool(
        _win_state->shm,
        shm_fd,
        static_cast<int32_t>(pool_size)
    );

    wl_display_roundtrip(_win_state->display);
#endif
    log::debug("Window created");
}

core::Window::~Window() {
    core::log::debug("Window closing");
#if defined(RAYGAME_GUI_WAYLAND)
    wl_display_disconnect(_win_state->display);
#endif
}

bool core::Window::should_close() {
    core::condition::pre_condition(
        _win_state->display != nullptr,
        "Cannot check if null window should close"
    );
    const bool close_now = (wl_display_dispatch(_win_state->display) != -1);
    core::log::debug(close_now ? "True" : "False");
    return close_now;
}
