#include "raygame/core/logger.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include "raygame/core/string.h"
#include "raygame/core/types.h"
#include <chrono>
#include <iostream>
#include <print>
#include <source_location>
#include <string>
#include <string_view>

namespace {

#if defined(RAYGAME_LOG_TRACE)
#    define RAYGAME_LOG_LEVEL TRACE
#elif defined(RAYGAME_LOG_DEBUG)
#    define RAYGAME_LOG_LEVEL DEBUG
#elif defined(RAYGAME_LOG_INFO)
#    define RAYGAME_LOG_LEVEL INFO
#elif defined(RAYGAME_LOG_WARNING)
#    define RAYGAME_LOG_LEVEL WARNING
#elif defined(RAYGAME_LOG_ERROR)
#    define RAYGAME_LOG_LEVEL ERROR
#elif defined(RAYGAME_LOG_FATAL)
#    define RAYGAME_LOG_LEVEL FATAL
#else
#    warning "No logging level set for RAYGAME, using NOTE"
constexpr Level logging_level = Level::NOTE;
#endif

//! Current logging level
constexpr core::log::Level logging_level = core::log::Level::RAYGAME_LOG_LEVEL;

constexpr std::string to_string(core::log::Level level) {
    switch (level) {
    case core::log::Level::TRACE:   return "TRACE";
    case core::log::Level::DEBUG:   return "DEBUG";
    case core::log::Level::INFO:    return "INFO ";
    case core::log::Level::WARNING: return "WARN ";
    case core::log::Level::ERROR:   return "ERROR";
    case core::log::Level::FATAL:   return "FATAL";
    }
    core::condition::unreachable();
}

using core::string::AnsiColour;

[[maybe_unused]]
constexpr AnsiColour level_colour(core::log::Level level) {
    switch (level) {
    case core::log::Level::TRACE:   return AnsiColour::CYAN;
    case core::log::Level::DEBUG:   return AnsiColour::GREEN;
    case core::log::Level::INFO:    return AnsiColour::BLUE;
    case core::log::Level::WARNING: return AnsiColour::YELLOW;
    case core::log::Level::ERROR:   return AnsiColour::RED;
    case core::log::Level::FATAL:   return AnsiColour::MAGENTA;
    }
    core::condition::unreachable();
}
} // namespace

void core::log::detail::logger(
    core::log::Level     level,
    std::string_view     text,
    std::source_location loc
) {
    if (logging_level <= level) {
        std::println(
            std::cerr,
            "{:%T} [{}]{} - {}",
            std::chrono::system_clock::now(),
            to_string(level),
            [loc] {
            const auto locmsg{core::debug::location_message(loc)};
            if (locmsg.empty()) {
                return std::string();
            }
            return " " + locmsg;
        }(),
            string::colourise(level_colour(level), text)
        );
    }
}
