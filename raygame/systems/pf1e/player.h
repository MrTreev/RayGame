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
    Name name;
    Sex  sex;
    Race race;

    size_t age;
    size_t height;
    size_t weight;

    Alignment alignment;
    Deity     deity;
};

struct Player: public Character {
    struct {
        core::int32_t strength;
        core::int32_t dexterity;
        core::int32_t constitution;
        core::int32_t intelligence;
        core::int32_t wisdom;
        core::int32_t charisma;
    } abilities;
};

} // namespace raygame::systems::pf1e
