#include "config.h"
#include <chrono>

const std::size_t config::start_time =
    std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    )
        .count();
