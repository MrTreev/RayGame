#pragma once
#include "raygame/core/types.h"
#include "raygame/systems/core/name.h"
#include "raygame/systems/core/sex.h"
#include "raygame/systems/pf1e/alignment.h"
#include "raygame/systems/pf1e/deity.h"
#include "raygame/systems/pf1e/race.h"
#include "raygame/systems/pf1e/skills.h"

namespace raygame::systems::pf1e {

struct EquipmentSlots {
    void* armour;
    void* belt;
    void* body;
    void* chest;
    void* eyes;
    void* feet;
    void* hands;
    void* headband;
    void* neck;
    void* ring_l;
    void* ring_r;
    void* shield;
    void* shoulders;
    void* wrist;
};

struct Character {
    Character(
        Name         name,
        Sex          sex,
        Race         race,
        core::size_t age,
        core::size_t height,
        core::size_t weight,
        Alignment    alignment,
        Deity        deity
    )
        : m_name(std::move(name))
        , m_sex(sex)
        , m_race(race)
        , m_age(age)
        , m_height(height)
        , m_weight(weight)
        , m_alignment(alignment)
        , m_deity(deity) {}

private:
    Name m_name;
    Sex  m_sex;
    Race m_race;

    core::size_t m_age;
    core::size_t m_height;
    core::size_t m_weight;

    Alignment m_alignment;
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
