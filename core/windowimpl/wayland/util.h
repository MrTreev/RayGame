#pragma once
#include "core/windowimpl/wayland/wayland_fwd.h"
#include <wayland-protocol.h>

int           allocate_shm_file(size_t size);
wl_shm_format get_colour_format();
