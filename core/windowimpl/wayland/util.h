#pragma once
#include <wayland-client-protocol.h>

int                allocate_shm_file(size_t size);
enum wl_shm_format get_colour_format();
