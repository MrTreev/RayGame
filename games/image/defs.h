#include "raygame/core/types.h"
#include <array>
#include <ranges>

namespace resources {

namespace detail {
template<typename T, size_t N>
using img_t =
    std::ranges::take_view<std::views::all_t<const std::array<T, N>&>>;
} // namespace detail

extern const detail::img_t<uint8_t, 35'329> img_argb8888;
} // namespace resources
