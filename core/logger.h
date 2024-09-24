#pragma once
#include "core/config.h"
#include "core/types.h"
#include <format>
#include <string>

namespace {
#if defined(RG_ENABLE_SOURCE_LOC)
constexpr bool enable_source_loc = true;
#else
constexpr bool enable_source_loc = false;
#endif
} // namespace

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
void logger(const core::log::Level& level, const std::string& text);
void logger(
    const core::log::Level&              level,
    const core::detail::source_location& loc,
    const std::string&                   text
);
} // namespace detail

#define MAKE_LOG_STRUCT(level, lvl)                                            \
    template<typename... Args>                                                 \
    struct level {                                                             \
        level(                                                                 \
            std::string                   msg,                                 \
            core::detail::source_location loc =                                \
                core::detail::source_location::current()                       \
        ) {                                                                    \
            if constexpr (enable_source_loc) {                                 \
                core::log::detail::logger(core::log::Level::lvl, loc, msg);    \
            } else {                                                           \
                std::ignore = loc;                                             \
                core::log::detail::logger(core::log::Level::lvl, msg);         \
            }                                                                  \
        }                                                                      \
        level(                                                                 \
            Args... args,                                                      \
            core::detail::source_location loc =                                \
                core::detail::source_location::current()                       \
        ) {                                                                    \
            if constexpr (enable_source_loc) {                                 \
                core::log::detail::logger(                                     \
                    core::log::Level::lvl,                                     \
                    loc,                                                       \
                    std::format(args...)                                       \
                );                                                             \
            } else {                                                           \
                std::ignore = loc;                                             \
                core::log::detail::logger(                                     \
                    core::log::Level::lvl,                                     \
                    std::format(args...)                                       \
                );                                                             \
            }                                                                  \
        }                                                                      \
    };                                                                         \
    template<typename... Args>                                                 \
    level(const char msg[]) -> level<>;                                        \
    template<typename... Args>                                                 \
    level(Args&&... args) -> level<Args...>;

MAKE_LOG_STRUCT(trace, TRACE);
MAKE_LOG_STRUCT(debug, DEBUG);
MAKE_LOG_STRUCT(info, INFO);
MAKE_LOG_STRUCT(note, NOTE);
MAKE_LOG_STRUCT(progress, PROGRESS);
MAKE_LOG_STRUCT(warning, WARNING);
MAKE_LOG_STRUCT(error, ERROR);
MAKE_LOG_STRUCT(fatal, FATAL);

#undef MAKE_LOG_STRUCT
} // namespace core::log
