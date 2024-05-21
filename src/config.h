#pragma once
#include <string_view>

namespace config {

//! Default window height
constexpr std::size_t default_window_height = 640;
//! Default window width
constexpr std::size_t default_window_width  = 480;

//! Target frame rate
constexpr std::size_t      frame_rate = 60;
//! Game name
constexpr std::string_view game_name  = "RayGame";

} // namespace config
