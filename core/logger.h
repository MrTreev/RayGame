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
void logger(const core::log::Level& level, const std::string& text RG_LOC_DEF);
} // namespace detail

inline void trace(const std::string& text RG_LOC_CUR) {
    core::log::detail::logger(Level::TRACE, text RG_LOC_VAR);
}

inline void debug(const std::string& text RG_LOC_CUR) {
    core::log::detail::logger(Level::DEBUG, text RG_LOC_VAR);
}

inline void info(const std::string& text RG_LOC_CUR) {
    core::log::detail::logger(Level::INFO, text RG_LOC_VAR);
}

inline void note(const std::string& text RG_LOC_CUR) {
    core::log::detail::logger(Level::NOTE, text RG_LOC_VAR);
}

inline void progress(const std::string& text RG_LOC_CUR) {
    core::log::detail::logger(Level::PROGRESS, text RG_LOC_VAR);
}

inline void warning(const std::string& text RG_LOC_CUR) {
    core::log::detail::logger(Level::WARNING, text RG_LOC_VAR);
}

inline void error(const std::string& text RG_LOC_CUR) {
    core::log::detail::logger(Level::ERROR, text RG_LOC_VAR);
}

inline void fatal(const std::string& text RG_LOC_CUR) {
    core::log::detail::logger(Level::FATAL, text RG_LOC_VAR);
}

} // namespace core::log
