#pragma once
#include "raygame/core/types.h"
#include <map>

namespace core::window {
class InputMapper {
    std::map<uint32_t, void (*)(uint32_t state)> m_map;

public:
    InputMapper();
    void map(uint32_t key, uint32_t state);
};
} // namespace core::window
