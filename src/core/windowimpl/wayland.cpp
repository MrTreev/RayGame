#include "core/windowimpl/wayland.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/math.h"
#include <algorithm>
#include <cerrno>
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
    const auto size   = numeric_cast<int32_t>(buffer_size);
    const int  shm_fd = allocate_shm_file(size);
    check_condition(shm_fd >= 0, "creation of shm buffer file failed");
    wayland_state.m_shm_data =
        mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (wayland_state.m_shm_data == MAP_FAILED) {
        close(shm_fd);
        check_condition(false, "Could not setup shm data");
    }
    struct wl_shm_pool* pool =
        wl_shm_create_pool(wayland_state.m_shm, shm_fd, size);
    struct wl_buffer* buffer = wl_shm_pool_create_buffer(
        pool,
        0,
        numeric_cast<int32_t>(width),
        numeric_cast<int32_t>(height),
        numeric_cast<int32_t>(width * 4),
        WL_SHM_FORMAT_ARGB8888
    );
    wl_shm_pool_destroy(pool);
    close(shm_fd);
    return buffer;
}
