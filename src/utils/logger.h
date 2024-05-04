#pragma once
#include <chrono>
#include <iostream>
#include <string>

#if defined(__cpp_lib_source_location)
#    include <source_location>
using std::source_location;
#else
#    include <experimental/source_location>
using std::experimental::source_location;
#endif

namespace utils {

using Level = enum: unsigned char {
    TRACE    = 0,
    DEBUG    = 10,
    INFO     = 20,
    NOTE     = 30,
    PROGRESS = 40,
    /* 50 - 80 */
    WARNING  = 80,
    ERROR    = 90,
    FATAL    = 255,
};

#if defined(RAYGAME_LOG_TRACE)
constexpr Level logging_level = Level::TRACE;
#elif defined(RAYGAME_LOG_DEBUG)
constexpr Level logging_level = Level::DEBUG;
#elif defined(RAYGAME_LOG_INFO)
constexpr Level logging_level = Level::INFO;
#elif defined(RAYGAME_LOG_NOTE)
constexpr Level logging_level = Level::NOTE;
#elif defined(RAYGAME_LOG_PROGRESS)
constexpr Level logging_level = Level::PROGRESS;
#elif defined(RAYGAME_LOG_WARNING)
constexpr Level logging_level = Level::WARNING;
#elif defined(RAYGAME_LOG_ERROR)
constexpr Level logging_level = Level::ERROR;
#elif defined(RAYGAME_LOG_FATAL)
constexpr Level logging_level = Level::FATAL;
#else
#    warning "No logging level set for RAYGAME, using NOTE"
constexpr Level logging_level = Level::NOTE;
#endif

inline std::string to_string(Level v) {
    switch (v) {
    case Level::TRACE:    return "TRACE";
    case Level::DEBUG:    return "DEBUG";
    case Level::INFO:     return "INFO ";
    case Level::NOTE:     return "NOTE ";
    case Level::PROGRESS: return "PROGR";
    case Level::WARNING:  return "WARN ";
    case Level::ERROR:    return "ERROR";
    case Level::FATAL:    return "FATAL";
    default:              static_cast<void>(v);
    }
}

namespace {
void logger(
    const utils::Level level,
    const std::string  text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const source_location loc = source_location::current()
#endif
) {
    const auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::system_clock::now().time_since_epoch()
    )
                             .count();
    std::cerr << time_ms << "-" << to_string(level)
#if defined(RAYGAME_LOG_LOCATION)
              << "-" << loc.file_name() << ":" << loc.line()
#endif
              << "-" << text << "\n";
};
} // namespace

namespace log {

inline void trace(std::string text) {
    if constexpr (logging_level >= Level::TRACE) {
        utils::logger(Level::TRACE, text);
    }
};

inline void debug(std::string text) {
    if constexpr (logging_level >= Level::DEBUG) {
        utils::logger(Level::DEBUG, text);
    }
};

inline void info(std::string text) {
    if constexpr (logging_level >= Level::INFO) {
        utils::logger(Level::INFO, text);
    }
};

inline void note(std::string text) {
    if constexpr (logging_level >= Level::NOTE) {
        utils::logger(Level::NOTE, text);
    }
};

inline void progress(std::string text) {
    if constexpr (logging_level >= Level::PROGRESS) {
        utils::logger(Level::PROGRESS, text);
    }
};

inline void warning(std::string text) {
    if constexpr (logging_level >= Level::WARNING) {
        utils::logger(Level::WARNING, text);
    }
};

inline void error(std::string text) {
    if constexpr (logging_level >= Level::ERROR) {
        utils::logger(Level::ERROR, text);
    }
};

inline void fatal(std::string text) {
    if constexpr (logging_level >= Level::FATAL) {
        utils::logger(Level::FATAL, text);
    }
};

} // namespace log
} // namespace utils
