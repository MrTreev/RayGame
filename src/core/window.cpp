#include "core/window.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/config.h"
#include "core/types.h"
#include <cstdlib>
#include <cstring>
#include <format>
#include <memory>
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

template<typename T>
constexpr inline T ceil_4(T num) {
    return (num + 3) & -4;
}

constexpr inline size_t cstrlen(const char* string) {
    return sizeof(string) - 1;
}

constexpr inline size_t cstrlen(const std::string& string) {
    return cstrlen(string.c_str());
}

int wayland_display_connect() {
    const std::string xdg_runtime_dir = std::getenv("XDG_RUNTIME_DIR");
    core::condition::check_condition(
        !xdg_runtime_dir.empty(),
        "Failed to get XDG_RUNTIME_DIR environment variable"
    );
    std::string wayland_display = std::getenv("WAYLAND_DISPLAY");
    if (wayland_display.empty()) {
        std::string wayland_display = "wayland-0";
    }
    const std::string sock_name = xdg_runtime_dir + "/" + wayland_display;

    struct sockaddr_un addr = {.sun_family = AF_UNIX};
    core::condition::check_condition(
        xdg_runtime_dir.length() <= (cstrlen(addr.sun_path)),
        "Failed to get valid socket"
    );

    std::memcpy(
        static_cast<void*>(addr.sun_path),
        xdg_runtime_dir.c_str(),
        xdg_runtime_dir.length()
    );

    size_t socket_path_len           = xdg_runtime_dir.length();
    addr.sun_path[socket_path_len++] = '/';

    std::memcpy(
        static_cast<void*>(addr.sun_path),
        wayland_display.c_str(),
        wayland_display.length()
    );
    int win_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    core::condition::check_condition(win_fd != -1, "Failed to create socket");
    core::condition::check_condition(
        connect(win_fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr))
            != 0,
        "Failed to connect to socket"
    );
    return win_fd;
}

class Buffer {
private:
    std::unique_ptr<char> _buffer;
    size_t                _buffer_size;
    size_t                _buffer_capacity;

public:
    template<typename T>
    void write(T msg);
    void write(std::string msg);
};

template<typename T>
void Buffer::write(T msg) {
    core::condition::pre_condition(
        _buffer_size + sizeof(T) <= _buffer_capacity,
        std::format("{} Too big for write", msg)
    );
    core::condition::pre_condition(
        (_buffer.get() + _buffer_size % sizeof(T) == nullptr),
        "Write not aligned"
    );
    static_cast<T*>(_buffer.get() + _buffer_size) = msg;
};

void Buffer::write(std::string msg) {
    core::condition::pre_condition(
        _buffer_size + msg.length() <= _buffer_capacity,
        std::format("{} Too big for write", msg)
    );
    core::condition::pre_condition(
        (_buffer.get() + _buffer_size % msg.size() == nullptr),
        "Write not aligned"
    );
    std::memcpy(_buffer.get() + _buffer_size, msg.c_str(), msg.length());
};

uint32_t wayland_get_registry(int win_fd) {}

} // namespace
#endif
