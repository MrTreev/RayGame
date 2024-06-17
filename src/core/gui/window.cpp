#include "core/gui/window.h" // IWYU pragma: keep
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
        xdg_runtime_dir.length() <= (sizeof(addr.sun_path) - 1),
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
