#pragma once
#include "raygame/core/types.h"
#include <functional>
#include <map>

namespace core {
class InputMapper {
public:
    using func_t = std::function<void(uint32_t)>;

private:
    std::map<uint32_t, func_t> m_map;

public:
    InputMapper();
    void map(uint32_t key, uint32_t state);
    void clear(uint32_t key);
    void set(uint32_t key, func_t func);
};
} // namespace core
