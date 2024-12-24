#include "raygame/core/types.h"

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

}
