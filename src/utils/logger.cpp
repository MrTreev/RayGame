#include "utils/logger.h"
#include <chrono>
#include <iostream>

using sysclock = std::chrono::system_clock;
using std::chrono::duration_cast;
using ms = std::chrono::milliseconds;

void
utils::logger(const utils::Level level, std::string text)
{
    if (static_cast<char>(logging_level) <= static_cast<char>(level))
    {
        const auto current_time = sysclock::now().time_since_epoch();
        const auto time_ms      = duration_cast<ms>(current_time).count();
        std::cerr << time_ms << " - " << ToString(level) << text << "\n";
    }
};
