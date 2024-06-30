#include "core/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/logger.h"
#include "core/math.h"
#include "core/types.h"
#include <wayland-client-protocol.h>

namespace {

constexpr size_t COLOUR_CHANNELS = 4;
constexpr size_t N_BUFFERS       = 2;
using core::condition::check_condition;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::log::debug;
using core::math::numeric_cast;
} // namespace

#if defined(RAYGAME_GUI_WAYLAND)
#    include <cstring>
#    include <fcntl.h>
#    include <random>
#    include <sys/mman.h>
#    include <wayland-client.h>
#endif

#if defined(RAYGAME_GUI_WAYLAND)
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

const struct wl_registry_listener registry_listener = {
    .global        = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};

struct core::WaylandWinState {
    std::string m_title;
    size_t      m_width       = 0;
    size_t      m_height      = 0;
    size_t      m_buffer_size = 0;
    int         m_shm_fd      = 0;

    std::unique_ptr<struct wl_compositor, decltype(free)*> m_compositor{
        static_cast<struct wl_compositor*>(malloc(sizeof m_compositor)),
        free
    };
    std::unique_ptr<struct wl_display, decltype(free)*> m_display{
        static_cast<struct wl_display*>(malloc(sizeof m_compositor)),
        free
    };
    std::unique_ptr<struct wl_registry, decltype(free)*> m_registry{
        static_cast<struct wl_registry*>(malloc(sizeof m_compositor)),
        free
    };
    std::unique_ptr<struct wl_shm, decltype(free)*> m_shm{
        static_cast<struct wl_shm*>(malloc(sizeof m_compositor)),
        free
    };
    std::unique_ptr<struct wl_shm_pool, decltype(free)*> m_shm_pool{
        static_cast<struct wl_shm_pool*>(malloc(sizeof m_compositor)),
        free
    };
    std::unique_ptr<struct wl_surface, decltype(free)*> m_surface{
        static_cast<struct wl_surface*>(malloc(sizeof m_compositor)),
        free
    };
};

namespace {

void registry_handle_global(
    void*               data,
    struct wl_registry* registry,
    uint32_t            name,
    const char*         interface,
    uint32_t            version
) {
    auto* state = static_cast<core::WaylandWinState*>(data);
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        state->m_compositor.reset(static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, 4)
        ));
        state->m_surface.reset(
            wl_compositor_create_surface(state->m_compositor.get())
        );
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        debug("shm: {}", interface);
        state->m_shm.reset(static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface, 1)
        ));
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
#endif

core::Window::Window(
    const core::Vec2<size_t>& size,
    const std::string&        title,
    const WindowStyle&        style
)
    : core::Window::Window(size.x, size.y, title, style) {}

core::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& title,
    const WindowStyle& style
)
    : m_win_state(std::make_unique<core::WaylandWinState>()) {
    debug("Constructing");
    m_win_state->m_title       = title;
    m_win_state->m_height      = height;
    m_win_state->m_width       = width;
    m_win_state->m_buffer_size = width * height;
#if defined(RAYGAME_GUI_WAYLAND)

    m_win_state->m_display = wl_display_connect(nullptr);
    check_condition(
        m_win_state->m_display != nullptr,
        "Unable to create Wayland display"
    );

    m_win_state->m_registry = wl_display_get_registry(m_win_state->m_display);
    check_condition(
        m_win_state->m_display != nullptr,
        "Unable to create Wayland registry"
    );

    wl_registry_add_listener(
        m_win_state->m_registry,
        &registry_listener,
        m_win_state.get()
    );
    debug("Registry Created");

    const auto stride          = numeric_cast<int>(width * COLOUR_CHANNELS);
    m_win_state->m_buffer_size = numeric_cast<int>(height * stride);
    const auto pool_size =
        numeric_cast<int>(m_win_state->m_buffer_size * N_BUFFERS);
    const int shm_fd = allocate_shm_file(pool_size);

    auto* pool_data = static_cast<uint8_t*>(
        mmap(nullptr, pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
    );
    debug("mmap Created");
    struct wl_shm_pool* m_shm_pool = wl_shm_create_pool(
        m_win_state->m_shm,
        shm_fd,
        static_cast<int32_t>(pool_size)
    );
    debug("shm_pool Created");

    wl_display_roundtrip(m_win_state->m_display);
#endif
    debug("Constructed");
}

core::Window::~Window() {
    debug("Destructing");
#if defined(RAYGAME_GUI_WAYLAND)
    wl_display_disconnect(m_win_state->m_display);
#endif
    debug("Destructed");
}

bool core::Window::should_close() {
    pre_condition(
        m_win_state->m_display != nullptr,
        "Cannot check if null window should close"
    );
    const bool close_now = (wl_display_dispatch(m_win_state->m_display) != -1);
    debug(close_now ? "True" : "False");
    return close_now;
}
