#include "games/image/cottage.h"
#include "games/image/defs.h"
#include "raygame/core/drawing/pixel.h"

namespace resources {
namespace {
template<typename T, unsigned long N>
consteval std::array<T, N - 1> arr2img(std::array<T, N> in_arr) {
    std::array<T, N - 1> out{};
    for (size_t i{0}; i < N - 1; i++) {
        // NOLINTNEXTLINE(*-constant-array-index)
        out[i] = in_arr[i];
    }
    return out;
}
} // namespace

const constinit std::array<core::Pixel, 92UL * 96UL> icon_argb8888 =
    std::bit_cast<std::array<core::Pixel, 92UL * 96UL>>(arr2img(cottage_image));
} // namespace resources
