#include "core/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/logger.h"
#include "core/math.h"
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
    std::string m_title;
    size_t      m_width       = 0;
    size_t      m_height      = 0;
    size_t      m_buffer_size = 0;
    int         m_shm_fd      = 0;

    const struct wl_registry_listener m_registry_listener = {
        .global        = registry_handle_global,
        .global_remove = registry_handle_global_remove,
    };

    struct wl_compositor* m_compositor = nullptr;
    struct wl_display*    m_display    = nullptr;
    struct wl_registry*   m_registry   = nullptr;
    struct wl_shm*        m_shm        = nullptr;
    struct wl_shm_pool*   m_shm_pool   = nullptr;
    struct wl_surface*    m_surface    = nullptr;
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
        state->m_compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, 4)
        );
        state->m_surface = wl_compositor_create_surface(state->m_compositor);
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        RG_PRINT_REG_INFO
        state->m_shm = static_cast<wl_shm*>(
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
    const int ret = ftruncate(shm_fd, core::math::numeric_cast<__off_t>(size));
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
    : m_win_state(std::make_unique<core::WaylandWinState>()) {
    core::log::debug("Window attempt");
    m_win_state->m_title       = title;
    m_win_state->m_height      = height;
    m_win_state->m_width       = width;
    m_win_state->m_buffer_size = width * height;
#if defined(RAYGAME_GUI_WAYLAND)

    m_win_state->m_display = wl_display_connect(nullptr);
    core::condition::check_condition(
        m_win_state->m_display != nullptr,
        "Unable to create Wayland display"
    );

    m_win_state->m_registry = wl_display_get_registry(m_win_state->m_display);
    core::condition::check_condition(
        m_win_state->m_display != nullptr,
        "Unable to create Wayland registry"
    );

    wl_registry_add_listener(
        m_win_state->m_registry,
        &m_win_state->m_registry_listener,
        &m_win_state
    );

    const size_t stride        = width * COLOUR_CHANNELS;
    m_win_state->m_buffer_size = height * stride;
    const size_t pool_size     = m_win_state->m_buffer_size * N_BUFFERS;
    const int    shm_fd        = allocate_shm_file(pool_size);

    auto* pool_data = static_cast<uint8_t*>(
        mmap(nullptr, pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
    );
    struct wl_shm_pool* pool = wl_shm_create_pool(
        m_win_state->m_shm,
        shm_fd,
        static_cast<int32_t>(pool_size)
    );

    wl_display_roundtrip(m_win_state->m_display);
#endif
    log::debug("Window created");
}

core::Window::~Window() {
    core::log::debug("Window closing");
#if defined(RAYGAME_GUI_WAYLAND)
    wl_display_disconnect(m_win_state->m_display);
#endif
}

bool core::Window::should_close() {
    core::condition::pre_condition(
        m_win_state->m_display != nullptr,
        "Cannot check if null window should close"
    );
    const bool close_now = (wl_display_dispatch(m_win_state->m_display) != -1);
    core::log::debug(close_now ? "True" : "False");
    return close_now;
}
