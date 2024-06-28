#pragma once
#include "core/config.h"
#include "core/types.h"
#include <format>
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
    }
}

namespace detail {

//! Logger implementation
template<class... Args>
void logger(
    const core::log::Level&     level,
    std::format_string<Args...> fmt,
    Args&&... args              RG_LOC_DEF
);
void logger(const core::log::Level& level, const std::string& text RG_LOC_DEF);
} // namespace detail

//! Log at an trace level
template<class... Args>
constexpr inline void
trace(std::format_string<Args...> fmt, Args&&... args RG_LOC_CUR) {
    if constexpr (logging_level <= Level::TRACE) {
        core::log::detail::logger(
            Level::TRACE,
            fmt,
            std::forward<Args...>(args)... RG_LOC_VAR
        );
    }
}

//! Log at an debug level
template<class... Args>
constexpr inline void
debug(std::format_string<Args...> fmt, Args&&... args RG_LOC_CUR) {
    if constexpr (logging_level <= Level::DEBUG) {
        core::log::detail::logger(
            Level::DEBUG,
            fmt,
            std::forward<Args...>(args)... RG_LOC_VAR
        );
    }
}

//! Log at an info level
template<class... Args>
constexpr inline void
info(std::format_string<Args...> fmt, Args&&... args RG_LOC_CUR) {
    if constexpr (logging_level <= Level::INFO) {
        core::log::detail::logger(
            Level::INFO,
            fmt,
            std::forward<Args...>(args)... RG_LOC_VAR
        );
    }
}

//! Log at an note level
template<class... Args>
constexpr inline void
note(std::format_string<Args...> fmt, Args&&... args RG_LOC_CUR) {
    if constexpr (logging_level <= Level::NOTE) {
        core::log::detail::logger(
            Level::NOTE,
            fmt,
            std::forward<Args...>(args)... RG_LOC_VAR
        );
    }
}

//! Log at an progress level
template<class... Args>
constexpr inline void
progress(std::format_string<Args...> fmt, Args&&... args RG_LOC_CUR) {
    if constexpr (logging_level <= Level::PROGRESS) {
        core::log::detail::logger(
            Level::PROGRESS,
            fmt,
            std::forward<Args...>(args)... RG_LOC_VAR
        );
    }
}

//! Log at an warning level
template<class... Args>
constexpr inline void
warning(std::format_string<Args...> fmt, Args&&... args RG_LOC_CUR) {
    if constexpr (logging_level <= Level::WARNING) {
        core::log::detail::logger(
            Level::WARNING,
            fmt,
            std::forward<Args...>(args)... RG_LOC_VAR
        );
    }
}

//! Log at an error level
template<class... Args>
constexpr inline void
error(std::format_string<Args...> fmt, Args&&... args RG_LOC_CUR) {
    if constexpr (logging_level <= Level::ERROR) {
        core::log::detail::logger(
            Level::ERROR,
            fmt,
            std::forward<Args...>(args)... RG_LOC_VAR
        );
    }
}

//! Log at a fatal level
template<class... Args>
constexpr inline void
fatal(std::format_string<Args...> fmt, Args&&... args RG_LOC_CUR) {
    if constexpr (logging_level <= Level::FATAL) {
        core::log::detail::logger(
            Level::FATAL RG_LOC_VAR,
            fmt,
            std::forward<Args...>(args)...
        );
    }
}

constexpr inline void trace(const std::string& text RG_LOC_CUR) {
    if constexpr (logging_level <= Level::TRACE) {
        core::log::detail::logger(Level::TRACE, text RG_LOC_VAR);
    }
}

constexpr inline void debug(const std::string& text RG_LOC_CUR) {
    if constexpr (logging_level <= Level::DEBUG) {
        core::log::detail::logger(Level::DEBUG, text RG_LOC_VAR);
    }
}

constexpr inline void info(const std::string& text RG_LOC_CUR) {
    if constexpr (logging_level <= Level::INFO) {
        core::log::detail::logger(Level::INFO, text RG_LOC_VAR);
    }
}

constexpr inline void note(const std::string& text RG_LOC_CUR) {
    if constexpr (logging_level <= Level::NOTE) {
        core::log::detail::logger(Level::NOTE, text RG_LOC_VAR);
    }
}

constexpr inline void progress(const std::string& text RG_LOC_CUR) {
    if constexpr (logging_level <= Level::PROGRESS) {
        core::log::detail::logger(Level::PROGRESS, text RG_LOC_VAR);
    }
}

constexpr inline void warning(const std::string& text RG_LOC_CUR) {
    if constexpr (logging_level <= Level::WARNING) {
        core::log::detail::logger(Level::WARNING, text RG_LOC_VAR);
    }
}

constexpr inline void error(const std::string& text RG_LOC_CUR) {
    if constexpr (logging_level <= Level::ERROR) {
        core::log::detail::logger(Level::ERROR, text RG_LOC_VAR);
    }
}

constexpr inline void fatal(const std::string& text RG_LOC_CUR) {
    if constexpr (logging_level <= Level::FATAL) {
        core::log::detail::logger(Level::FATAL, text RG_LOC_VAR);
    }
}

} // namespace core::log
