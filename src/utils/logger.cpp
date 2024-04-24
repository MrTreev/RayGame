#include "utils/logger.h"
#include <cassert>
#include <iostream>

namespace utils {

template <typename T>
void logger(const Level level, const T &text) {
    if (logging_level >= level) {
        std::cerr << ToString(level) << text << "\n";
    }
};

std::string ToString(Level v) {
    switch (v) {
        case Level::TRACE:    return "TRACE   ";
        case Level::DEBUG:    return "DEBUG   ";
        case Level::INFO:     return "INFO    ";
        case Level::NOTE:     return "NOTE    ";
        case Level::PROGRESS: return "PROGRESS";
        case Level::WARNING:  return "WARNING ";
        case Level::ERROR:    return "ERROR   ";
        case Level::FATAL:    return "FATAL   ";
        default:              assert(false);
    }
}
} // namespace utils
