#pragma once
#include "core/include/stdint.h"

namespace core::gui {

class Window {
public:
    Window();
    Window(const uint32_t& width, const uint32_t& height);
};

} // namespace core::gui
