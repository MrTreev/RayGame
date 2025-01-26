#include "games/image/cottage.h"
#include "games/image/defs.h"

namespace resources {
const std::array<uint8_t, (92UL * 96UL * 4UL) + 1> icon_argb8888 =
    std::to_array(cottage_image.pixel_data);

const detail::img_t<uint8_t, 35'329> img_argb8888 =
    std::ranges::views::take(icon_argb8888, icon_argb8888.size() - 1);
} // namespace resources
