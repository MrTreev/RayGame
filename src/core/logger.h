#pragma once
#include <string>

#if defined(RAYGAME_LOG_LOCATION)
#    if __has_include(<experimental/source_location>)
#        include <experimental/source_location>
#    elif __has_include(<source_location>)
#        include <source_location>
#    else
#        undef RAYGAME_LOG_LOCATION
#    endif
#endif

namespace core::log {

//! Logging level
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

//! Logging level to string converter
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

#if __has_include(<experimental/source_location>)
using std::experimental::source_location;
#elif __has_include(<source_location>)
using std::source_location;
#endif

//! Logger implementation
void logger(
    const core::log::Level& level,
    const std::string&      text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const source_location& loc = source_location::current()
#endif
);
} // namespace detail

//! Log at an trace level
inline void trace(const std::string& text) {
    if constexpr (logging_level >= Level::TRACE) {
        core::log::detail::logger(Level::TRACE, text);
    }
}

//! Log at an debug level
inline void debug(const std::string& text) {
    if constexpr (logging_level >= Level::DEBUG) {
        core::log::detail::logger(Level::DEBUG, text);
    }
}

//! Log at an info level
inline void info(const std::string& text) {
    if constexpr (logging_level >= Level::INFO) {
        core::log::detail::logger(Level::INFO, text);
    }
}

//! Log at an note level
inline void note(const std::string& text) {
    if constexpr (logging_level >= Level::NOTE) {
        core::log::detail::logger(Level::NOTE, text);
    }
}

//! Log at an progress level
inline void progress(const std::string& text) {
    if constexpr (logging_level >= Level::PROGRESS) {
        core::log::detail::logger(Level::PROGRESS, text);
    }
}

//! Log at an warning level
inline void warning(const std::string& text) {
    if constexpr (logging_level >= Level::WARNING) {
        core::log::detail::logger(Level::WARNING, text);
    }
}

//! Log at an error level
inline void error(const std::string& text) {
    if constexpr (logging_level >= Level::ERROR) {
        core::log::detail::logger(Level::ERROR, text);
    }
}

//! Log at a fatal level
inline void fatal(const std::string& text) {
    if constexpr (logging_level >= Level::FATAL) {
        core::log::detail::logger(Level::FATAL, text);
    }
}

} // namespace core::log
