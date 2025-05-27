#pragma once
#include "raygame/core/types.h"

namespace raygame::systems::pf1e {
class Coins {
    core::size_t m_amount{0};

    static constexpr core::size_t PP_ = 1000;
    static constexpr core::size_t GP_ = 100;
    static constexpr core::size_t SP_ = 10;
    static constexpr core::size_t CP_ = 1;

public:
    constexpr Coins() = default;

    constexpr explicit Coins(core::size_t amount)
        : m_amount(amount) {}

    [[nodiscard]]
    constexpr core::size_t pp() const {
        return m_amount / PP_;
    }

    [[nodiscard]]
    constexpr core::size_t gp() const {
        return m_amount / GP_;
    }

    [[nodiscard]]
    constexpr core::size_t sp() const {
        return m_amount / SP_;
    }

    [[nodiscard]]
    constexpr core::size_t cp() const {
        return m_amount / CP_;
    }
};

} // namespace raygame::systems::pf1e
