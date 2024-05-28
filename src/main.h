#pragma once
#include "core/config.h"
#include "core/types.h"
#include <chrono>
#include <string_view>

namespace config {

//! Default window width
constexpr std::size_t window_width  = 480;
//
//! Default window height
constexpr std::size_t window_height = 640;

//! Default frame rate
constexpr std::size_t frame_rate = 60;

//! Game name
constexpr std::string_view game_name = "RayGame";

const size_t start_time =
    static_cast<size_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch()
    )
                            .count());

} // namespace config
