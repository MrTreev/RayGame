#pragma once
#include "core/config.h"
#include "core/types.h"
#include <string>

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
    case Level::TRACE:    return "TRACE";
    case Level::DEBUG:    return "DEBUG";
    case Level::INFO:     return "INFO ";
    case Level::NOTE:     return "NOTE ";
    case Level::PROGRESS: return "PROGR";
    case Level::WARNING:  return "WARN ";
    case Level::ERROR:    return "ERROR";
    case Level::FATAL:    return "FATAL";
    }
}

namespace detail {

//! Logger implementation
void logger(
    const core::log::Level& level,
    const std::string&      text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const core::detail::source_location& loc
#endif
);
} // namespace detail

//! Log at an trace level
inline void trace(
    const std::string& text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
#endif
) {
    if constexpr (logging_level <= Level::TRACE) {
        core::log::detail::logger(
            Level::TRACE,
            text
#if defined(RAYGAME_LOG_LOCATION)
            ,
            loc
#endif
        );
    }
}

//! Log at an debug level
inline void debug(
    const std::string& text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
#endif
) {
    if constexpr (logging_level <= Level::DEBUG) {
        core::log::detail::logger(
            Level::DEBUG,
            text
#if defined(RAYGAME_LOG_LOCATION)
            ,
            loc
#endif
        );
    }
}

//! Log at an info level
inline void info(
    const std::string& text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
#endif
) {
    if constexpr (logging_level <= Level::INFO) {
        core::log::detail::logger(
            Level::INFO,
            text
#if defined(RAYGAME_LOG_LOCATION)
            ,
            loc
#endif
        );
    }
}

//! Log at an note level
inline void note(
    const std::string& text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
#endif
) {
    if constexpr (logging_level <= Level::NOTE) {
        core::log::detail::logger(
            Level::NOTE,
            text
#if defined(RAYGAME_LOG_LOCATION)
            ,
            loc
#endif
        );
    }
} //! Log at an progress level

inline void progress(
    const std::string& text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
#endif
) {
    if constexpr (logging_level <= Level::PROGRESS) {
        core::log::detail::logger(
            Level::PROGRESS,
            text
#if defined(RAYGAME_LOG_LOCATION)
            ,
            loc
#endif
        );
    }
}

//! Log at an warning level
inline void warning(
    const std::string& text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
#endif
) {
    if constexpr (logging_level <= Level::WARNING) {
        core::log::detail::logger(
            Level::WARNING,
            text
#if defined(RAYGAME_LOG_LOCATION)
            ,
            loc
#endif
        );
    }
}

//! Log at an error level
inline void error(
    const std::string& text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
#endif
) {
    if constexpr (logging_level <= Level::ERROR) {
        core::log::detail::logger(
            Level::ERROR,
            text
#if defined(RAYGAME_LOG_LOCATION)
            ,
            loc
#endif
        );
    }
}

//! Log at a fatal level
inline void fatal(
    const std::string& text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
#endif
) {
    if constexpr (logging_level <= Level::FATAL) {
        core::log::detail::logger(
            Level::FATAL,
            text
#if defined(RAYGAME_LOG_LOCATION)
            ,
            loc
#endif
        );
    }
}

} // namespace core::log
