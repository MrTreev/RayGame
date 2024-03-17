#include "utils/logger.h"
#include <iostream>

namespace utils {

void Logger::log(const Level level, const std::string &text) {
    if (level >= get_level()) {
        std::cerr << level << text << "\n";
        if (level == FATAL) { exit(1); }
    }
}

void Logger::log(const Level level, const std::ostringstream &stream) {
    if (level >= get_level()) {
        std::cerr << level << stream.str() << "\n";
        if (level == FATAL) { exit(1); }
    }
}

void Logger::log(const Level level, const char *text) {
    if (level >= get_level()) {
        std::cerr << level << text << "\n";
        if (level == FATAL) { exit(1); }
    }
}

} // namespace utils
