#include "raygame/core/application/input.hpp" // IWYU pragma: keep
#include "raygame/core/logger.hpp"
#include "raygame/core/types.hpp"
#include <utility>

// NOLINTNEXTLINE(*-easily-swappable-parameters)
void core::InputMapper::map(const uint32_t key, const uint32_t state) {
    const auto val = m_map.find(key);
    if (val != m_map.end()) {
        val->second(state);
    } else {
        core::log::debug("Missed map: state {}, key: {}, ", state, key);
    }
}

void core::InputMapper::clear(uint32_t key) {
    m_map.erase(key);
}

void core::InputMapper::set(uint32_t key, func_t func) {
    m_map.insert_or_assign(key, std::move(func));
}
