#include "raygame/core/base/types.h"
#include "raygame/core/math/arithmetic.h"

namespace raygame::systems::pf1e {
class Coins {
    size_t m_amount{0};

    static constexpr size_t PP = 1000;
    static constexpr size_t GP = 100;
    static constexpr size_t SP = 10;
    static constexpr size_t CP = 1;

public:
    Coins() = default;

    Coins(size_t amount)
        : m_amount(amount) {}

    size_t pp() {
        return m_amount / PP;
    }

    size_t gp() {
        return m_amount / GP;
    }

    size_t sp() {
        return m_amount / SP;
    }

    size_t cp() {
        return m_amount / CP;
    }
};

} // namespace raygame::systems::pf1e
