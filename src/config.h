#pragma once
#include <string_view>

namespace config {

constexpr std::size_t default_window_height = 800;
constexpr std::size_t default_window_width  = 450;

constexpr std::size_t      frame_rate = 60;
constexpr std::string_view game_name  = "RayGame";

} // namespace config
