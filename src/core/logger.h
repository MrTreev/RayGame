#pragma once
#include "core/config.h"
#include "core/types.h"
#include <string>
#include <utility>

namespace core::log {

//! Logging level
enum class Level : uint8_t {
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
    case Level::TRACE:
        return "TRACE";
    case Level::DEBUG:
        return "DEBUG";
    case Level::INFO:
        return "INFO ";
    case Level::NOTE:
        return "NOTE ";
    case Level::PROGRESS:
        return "PROG ";
    case Level::WARNING:
        return "WARN ";
    case Level::ERROR:
        return "ERROR";
    case Level::FATAL:
        return "FATAL";
    default:
        std::unreachable();
    }
}

namespace detail {
void logger(
    const core::log::Level&              level,
    const std::string&                   text,
    const core::detail::source_location& loc
);
} // namespace detail

inline void trace(
    const std::string&                   text,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    core::log::detail::logger(Level::TRACE, text, loc);
}

inline void debug(
    const std::string&                   text,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    core::log::detail::logger(Level::DEBUG, text, loc);
}

inline void info(
    const std::string&                   text,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    core::log::detail::logger(Level::INFO, text, loc);
}

inline void note(
    const std::string&                   text,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    core::log::detail::logger(Level::NOTE, text, loc);
}

inline void progress(
    const std::string&                   text,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    core::log::detail::logger(Level::PROGRESS, text, loc);
}

inline void warning(
    const std::string&                   text,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    core::log::detail::logger(Level::WARNING, text, loc);
}

inline void error(
    const std::string&                   text,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    core::log::detail::logger(Level::ERROR, text, loc);
}

inline void fatal(
    const std::string&                   text,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    core::log::detail::logger(Level::FATAL, text, loc);
}

} // namespace core::log
