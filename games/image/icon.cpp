#include "games/image/cottage.h"
#include "games/image/defs.h"

namespace resources {
const std::array<uint8_t, (92UL * 96UL * 4UL) + 1> icon_argb8888 =
    std::to_array(cottage_image.pixel_data);
} // namespace resources
