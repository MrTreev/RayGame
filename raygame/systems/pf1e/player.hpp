#pragma once
#include "raygame/core/types.hpp"
#include "raygame/systems/core/name.hpp"
#include "raygame/systems/core/sex.hpp"
#include "raygame/systems/pf1e/alignment.hpp"
#include "raygame/systems/pf1e/deity.hpp"
#include "raygame/systems/pf1e/race.hpp"

namespace raygame::systems::pf1e {

struct EquipmentSlots {
    void* m_armour;
    void* m_belt;
    void* m_body;
    void* m_chest;
    void* m_eyes;
    void* m_feet;
    void* m_hands;
    void* m_headband;
    void* m_neck;
    void* m_ring_l;
    void* m_ring_r;
    void* m_shield;
    void* m_shoulders;
    void* m_wrist;
};

struct Character {
    Name m_name{""};
    Sex  m_sex{};
    Race m_race{};

    core::size_t m_age{};
    core::size_t m_height{};
    core::size_t m_weight{};

    Alignment m_alignment{};
    Deity     m_deity;
};

struct Player: public Character {
    struct {
        core::int32_t m_strength;
        core::int32_t m_dexterity;
        core::int32_t m_constitution;
        core::int32_t m_intelligence;
        core::int32_t m_wisdom;
        core::int32_t m_charisma;
    } m_abilities{};
};

} // namespace raygame::systems::pf1e
