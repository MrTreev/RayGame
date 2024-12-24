#include "raygame/core/types.h"

namespace raygame::systems::pf1e {
class Coins {
    size_t m_amount{0};

    static constexpr size_t PP = 1000;
    static constexpr size_t GP = 100;
    static constexpr size_t SP = 10;
    static constexpr size_t CP = 1;

public:
    constexpr Coins() = default;

    constexpr Coins(size_t amount)
        : m_amount(amount) {}

    constexpr size_t pp() {
        return m_amount / PP;
    }

    constexpr size_t gp() {
        return m_amount / GP;
    }

    constexpr size_t sp() {
        return m_amount / SP;
    }

    constexpr size_t cp() {
        return m_amount / CP;
    }
};

} // namespace raygame::systems::pf1e
