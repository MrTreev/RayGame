#include "core/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/config.h"
#include "core/image.h"
#include "core/types.h"
#include <cstddef>
#include <fcntl.h>
#include <memory>
#include <sys/mman.h>
#if defined(RAYGAME_OS_LINUX)
#    include <sys/socket.h>
#    include <sys/un.h>
#endif

#if defined(RAYGAME_GUI_WAYLAND)
namespace {

constexpr uint32_t wayland_display_object_id                   = 1;
constexpr uint16_t wayland_wl_registry_event_global            = 0;
constexpr uint16_t wayland_shm_pool_event_format               = 0;
constexpr uint16_t wayland_wl_buffer_event_release             = 0;
constexpr uint16_t wayland_xdg_wm_base_event_ping              = 0;
constexpr uint16_t wayland_xdg_toplevel_event_configure        = 0;
constexpr uint16_t wayland_xdg_toplevel_event_close            = 1;
constexpr uint16_t wayland_xdg_surface_event_configure         = 0;
constexpr uint16_t wayland_wl_display_get_registry_opcode      = 1;
constexpr uint16_t wayland_wl_registry_bind_opcode             = 0;
constexpr uint16_t wayland_wl_compositor_create_surface_opcode = 0;
constexpr uint16_t wayland_xdg_wm_base_pong_opcode             = 3;
constexpr uint16_t wayland_xdg_surface_ack_configure_opcode    = 4;
constexpr uint16_t wayland_wl_shm_create_pool_opcode           = 0;
constexpr uint16_t wayland_xdg_wm_base_get_xdg_surface_opcode  = 2;
constexpr uint16_t wayland_wl_shm_pool_create_buffer_opcode    = 0;
constexpr uint16_t wayland_wl_surface_attach_opcode            = 1;
constexpr uint16_t wayland_xdg_surface_get_toplevel_opcode     = 1;
constexpr uint16_t wayland_wl_surface_commit_opcode            = 6;
constexpr uint16_t wayland_wl_display_error_event              = 0;
constexpr uint32_t wayland_format_xrgb8888                     = 1;
constexpr uint32_t wayland_header_size                         = 8;
constexpr uint32_t color_channels                              = 4;

enum class state_type {
    STATE_NONE,
    STATE_SURFACE_ACKED_CONFIGURE,
    STATE_SURFACE_ATTACHED,
};

using frame_buffer = std::unique_ptr<std::vector<core::Pixel>>;

struct WindowState {
    uint32_t     height;
    uint32_t     width;
    uint32_t     stride;
    uint32_t     shm_pool_size;
    uint32_t     wl_buffer;
    uint32_t     wl_registry;
    uint32_t     wl_shm;
    uint32_t     wl_shm_pool;
    uint32_t     xdg_surface;
    uint32_t     xdg_toplevel;
    uint32_t     xdg_wm_base;
    int          shm_fd;
    state_type   state;
    frame_buffer front_buffer;
    frame_buffer back_buffer;
} _state;

} // namespace

core::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name,
    const WindowStyle& style
) {
    char shared_buffers[255];
    _state.width  = width;
    _state.height = height;
    _state.stride = width * sizeof(core::Pixel);
    _state.front_buffer->reserve(
        static_cast<size_t>(_state.stride) * static_cast<size_t>(_state.height)
    );
    _state.back_buffer->reserve(
        static_cast<size_t>(_state.stride) * static_cast<size_t>(_state.height)
    );
    _state.shm_fd = shm_open(shared_buffers, O_RDWR | O_EXCL | O_CREAT, 0600);
    condition::check_condition(
        _state.shm_fd != -1,
        "Shared memory file descriptor could not be opened"
    );
}

core::Window::~Window() {}

bool core::Window::should_close() {}

#endif
