#pragma once
#include <string>

#if defined(RAYGAME_LOG_LOCATION)
#    include <source_location>
#endif

namespace core::utils {

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

inline std::string to_string(Level level) {
    switch (level) {
    case Level::TRACE:    return "TRACE";
    case Level::DEBUG:    return "DEBUG";
    case Level::INFO:     return "INFO ";
    case Level::NOTE:     return "NOTE ";
    case Level::PROGRESS: return "PROGR";
    case Level::WARNING:  return "WARN ";
    case Level::ERROR:    return "ERROR";
    case Level::FATAL:    return "FATAL";
    default:              return "     "; // std::unreachable(); in c++23
    }
}

namespace detail {
void logger(
    const core::utils::Level& level,
    const std::string&        text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const source_location loc = source_location::current()
#endif
);
} // namespace detail

namespace log {

inline void trace(const std::string& text) {
    if constexpr (logging_level >= Level::TRACE) {
        core::utils::detail::logger(Level::TRACE, text);
    }
}

inline void debug(const std::string& text) {
    if constexpr (logging_level >= Level::DEBUG) {
        core::utils::detail::logger(Level::DEBUG, text);
    }
}

inline void info(const std::string& text) {
    if constexpr (logging_level >= Level::INFO) {
        core::utils::detail::logger(Level::INFO, text);
    }
}

inline void note(const std::string& text) {
    if constexpr (logging_level >= Level::NOTE) {
        core::utils::detail::logger(Level::NOTE, text);
    }
}

inline void progress(const std::string& text) {
    if constexpr (logging_level >= Level::PROGRESS) {
        core::utils::detail::logger(Level::PROGRESS, text);
    }
}

inline void warning(const std::string& text) {
    if constexpr (logging_level >= Level::WARNING) {
        core::utils::detail::logger(Level::WARNING, text);
    }
}

inline void error(const std::string& text) {
    if constexpr (logging_level >= Level::ERROR) {
        core::utils::detail::logger(Level::ERROR, text);
    }
}

inline void fatal(const std::string& text) {
    if constexpr (logging_level >= Level::FATAL) {
        core::utils::detail::logger(Level::FATAL, text);
    }
}

} // namespace log
} // namespace core::utils
