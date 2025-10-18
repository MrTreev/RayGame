#include "raygame/core/window/input.h" // IWYU pragma: keep

core::window::InputMapper::InputMapper() = default;

// NOLINTNEXTLINE(*-easily-swappable-parameters)
void core::window::InputMapper::map(const uint32_t key, const uint32_t state) {
    const auto val = m_map.find(key);
    if (val != m_map.end()) {
        (val->second)(state);
    }
}

void core::window::InputMapper::clear(uint32_t key) {
    m_map.erase(key);
}

void core::window::InputMapper::set(uint32_t key, func_t func) {
    m_map.insert_or_assign(key, func);
}
