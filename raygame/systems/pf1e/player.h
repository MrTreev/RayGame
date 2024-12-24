#include "raygame/core/types.h"
#include "raygame/systems/core/name.h"
#include "raygame/systems/core/sex.h"
#include "raygame/systems/pf1e/skills.h"

namespace raygame::systems::pf1e {

enum class Size : uint8_t {
    Fine           = 0x01,
    Diminutive     = 0x02,
    Tiny           = 0x03,
    Small          = 0x04,
    Medium         = 0x05,
    LargeTall      = 0x06,
    LargeLong      = 0x07,
    HugeTall       = 0x08,
    HugeLong       = 0x09,
    GargantuanTall = 0x0A,
    GargantuanLong = 0x0B,
    ColossalTall   = 0x0C,
    ColossalLong   = 0x0D,
};

enum class Alignment : uint8_t {
    // clang-format off
    CG, NG, LG,
    CN, TN, LN,
    CE, NE, LE,
    // clang-format on
};

struct Race {
    size_t starting_feats;
    Size   size;
};

struct Class {
    static constexpr size_t starting_wealth{};
};

struct Deity {};

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
