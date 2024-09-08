#include "core/windowimpl/wayland/util.h" // IWYU pragma: keep
#include "core/colours.h"
#include "core/condition.h"
#include "core/math.h"
#include <fcntl.h>
#include <format>
#include <random>
#include <string>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>

using core::condition::check_condition;
using core::condition::post_condition;
using core::condition::pre_condition;
using core::math::numeric_cast;

static constexpr std::string_view alnum =
    "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

static std::string random_string(
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

static int create_shm_file() {
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

wl_shm_format get_colour_format() {
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
