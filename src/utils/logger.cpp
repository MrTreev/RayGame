#include "utils/logger.h"
#include <chrono>
#include <iostream>

void utils::logger(const utils::Level level, std::string text) {
    if (static_cast<char>(logging_level) <= static_cast<char>(level)) {
        const auto current_time = std::chrono::system_clock::now();
        std::cerr << current_time << " - " << ToString(level) << text << "\n";
    }
};
