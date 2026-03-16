#include "raygame/core/logger.h" // IWYU pragma: keep
#include "raygame/core/config.h"
#include "raygame/core/string.h"
#include "raygame/core/types.h"
#include <chrono>
#include <cstdlib>
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
RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
RAYGAME_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")
RAYGAME_DEBUG_ONLY(const)
RAYGAME_RELEASE_ONLY(constexpr)
//NOLINTNEXTLINE(cert-err58-cpp)
core::log::Level logging_level = []() {
    if constexpr (core::config::BUILD_TYPE == core::config::BuildType::DEBUG) {
        //NOLINTNEXTLINE(concurrency-mt-unsafe)
        const char* const lvl{std::getenv("RAYGAME_LOG_LEVEL")};
        if (lvl != nullptr) {
            const auto level = std::string(lvl);
            if (level == "TRACE") {
                return core::log::Level::TRACE;
            }
            if (level == "DEBUG") {
                return core::log::Level::DEBUG;
            }
            if (level == "INFO") {
                return core::log::Level::INFO;
            }
            if (level == "WARNING") {
                return core::log::Level::WARNING;
            }
            if (level == "ERROR") {
                return core::log::Level::ERROR;
            }
            if (level == "FATAL") {
                return core::log::Level::FATAL;
            }
        }
    }
    return core::log::Level::RAYGAME_LOG_LEVEL;
}();
RAYGAME_CLANG_SUPPRESS_WARNING_POP

constexpr std::string to_string(core::log::Level level) {
    switch (level) {
    case core::log::Level::TRACE:   return "TRACE";
    case core::log::Level::DEBUG:   return "DEBUG";
    case core::log::Level::INFO:    return "INFO ";
    case core::log::Level::WARNING: return "WARN ";
    case core::log::Level::ERROR:   return "ERROR";
    case core::log::Level::FATAL:   return "FATAL";
    }
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
