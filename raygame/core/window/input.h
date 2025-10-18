#pragma once
#include "raygame/core/types.h"
#include <map>

namespace core::window {
class InputMapper {
    using func_t = void (*)(uint32_t);
    std::map<uint32_t, void (*)(uint32_t)> m_map;

public:
    InputMapper();
    void map(uint32_t key, uint32_t state);
    void clear(uint32_t key);
    void set(uint32_t key, func_t func);
};
} // namespace core::window
