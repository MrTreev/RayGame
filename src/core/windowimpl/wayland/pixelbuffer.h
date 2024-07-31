#pragma once
#include "core/types.h"

namespace core::window::wayland {

class PixelBuffer {
    const size_t m_width;
    const size_t m_height;
    const size_t m_buffer_size;

public:
    PixelBuffer() = delete;
    ~PixelBuffer();
};

} // namespace core::window::wayland
