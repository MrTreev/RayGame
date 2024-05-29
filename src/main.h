#pragma once
#include "core/types.h"
#include <chrono>
#include <string_view>

namespace config {

//! Default window width
#if defined(RAYGAME_GAME_WIDTH)
constexpr std::size_t window_width = RAYGAME_WINDOW_WIDTH;
#else
constexpr std::size_t window_width = 640;
#endif

//! Default window height
#if defined(RAYGAME_GAME_HEIGHT)
constexpr std::size_t window_height = RAYGAME_GAME_HEIGHT;
#else
constexpr std::size_t window_height = 480;
#endif

//! Default frame rate
#if defined(RAYGAME_GAME_FPS)
constexpr std::size_t frame_rate = RAYGAME_GAME_FPS;
#else
constexpr std::size_t frame_rate = 60;
#endif

//! Game name
#if defined(RAYGAME_GAME_NAME)
constexpr std::string_view game_name = RAYGAME_GAME_NAME;
#else
constexpr std::string_view game_name = "RayGame";
#endif

const size_t start_time =
    static_cast<size_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch()
    )
                            .count());

} // namespace config
