#include "raygame/core/window/input.h" // IWYU pragma: keep

core::window::InputMapper::InputMapper() = default;

void core::window::InputMapper::map(const uint32_t key, const uint32_t state) {
    std::ignore = key;
    std::ignore = state;
}
