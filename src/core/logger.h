#pragma once
#include "core/types.h"
#include <string>

#if defined(RAYGAME_LOG_LOCATION)
#    if __has_include(<experimental/source_location>)
#        include <experimental/source_location>

namespace core::detail {
using std::experimental::source_location;
}
#    elif __has_include(<source_location>)
#        include <source_location>

namespace core::detail {
using std::source_location;
}
#    else
#        warn "source_location unsupported, disabling RAYGAME_LOG_LOCATION"
#        undef RAYGAME_LOG_LOCATION
#    endif
#endif

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
        return "PROGR";
    case Level::WARNING:
        return "WARN ";
    case Level::ERROR:
        return "ERROR";
    case Level::FATAL:
        return "FATAL";
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
constexpr inline void trace(
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
constexpr inline void debug(
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
constexpr inline void info(
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
constexpr inline void note(
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

constexpr inline void progress(
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
constexpr inline void warning(
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
constexpr inline void error(
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
constexpr inline void fatal(
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
