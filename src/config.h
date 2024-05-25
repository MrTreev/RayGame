#pragma once
#include <string_view>

#if defined(RAYGAME_LOG_LOCATION)
#    if __has_include(<experimental/source_location>)
#        include <experimental/source_location>

namespace config::detail {
using std::experimental::source_location;
}
#    elif __has_include(<source_location>)
#        include <source_location>

namespace config::detail {
using std::source_location;
}
#    else
#        undef RAYGAME_LOG_LOCATION
#    endif
#endif

namespace config {

//! Default window height
constexpr std::size_t default_window_height = 640;
//! Default window width
constexpr std::size_t default_window_width  = 480;

//! Target frame rate
constexpr std::size_t      frame_rate = 60;
//! Game name
constexpr std::string_view game_name  = "RayGame";

extern const std::size_t start_time;

#if defined(RAYGAME_LOG_LOCATION)
namespace {
constexpr std::size_t get_prefix_len(
    const config::detail::source_location loc =
        config::detail::source_location::current()
) {
    const std::string_view locname    = loc.file_name();
    const std::size_t      nopref_len = locname.rfind('/');
    return nopref_len + 1;
}
} // namespace

constexpr std::size_t path_count = get_prefix_len();
#endif

} // namespace config
