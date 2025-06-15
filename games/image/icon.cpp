#include "games/image/icon.h"
#include "games/image/cottage.h"
#include "games/image/defs.h"
#include "raygame/core/drawing/pixel.h"

namespace resources {
namespace {
template<typename T, unsigned long N>
constexpr std::array<T, N - 1> arr2img(std::array<T, N> in_arr) {
    std::array<T, N - 1> out{};
    std::copy_n(in_arr.begin(), N - 1, out.begin());
    return out;
}
} // namespace

[[maybe_unused]]
constinit const std::array<core::Pixel, 92UL * 96UL> icon_argb8888 =
    std::bit_cast<std::array<core::Pixel, 92UL * 96UL>>(arr2img(cottage_image));
[[maybe_unused]]
constinit const std::array<core::Pixel, 400UL * 400UL> img_icon =
    std::bit_cast<std::array<core::Pixel, 400UL * 400UL>>(arr2img(pixel_data));
} // namespace resources
