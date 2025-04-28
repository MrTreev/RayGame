#include "raygame/core/logger.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include <chrono>
#include <iostream>
#include <source_location>
#include <string_view>

namespace {
#if defined(RAYGAME_ENABLE_SOURCE_LOCATION)
constexpr bool enable_source_loc = true;
#elif defined(RAYGAME_DISABLE_SOURCE_LOCATION)
constexpr bool enable_source_loc = false;
#else
#    warning "No source location macro defined, disabling"
constexpr bool enable_source_loc = false;
#endif

constexpr std::string to_string(core::log::Level level) {
    switch (level) {
    case core::log::Level::TRACE:    return "TRACE";
    case core::log::Level::DEBUG:    return "DEBUG";
    case core::log::Level::INFO:     return "INFO ";
    case core::log::Level::NOTE:     return "NOTE ";
    case core::log::Level::PROGRESS: return "PROG ";
    case core::log::Level::WARNING:  return "WARN ";
    case core::log::Level::ERROR:    return "ERROR";
    case core::log::Level::FATAL:    return "FATAL";
    }
    core::condition::unreachable();
}

constexpr std::string location_string(std::source_location loc) {
    if (enable_source_loc) {
        constexpr std::string_view search_str = "/raygame/";
        std::string_view           shortloc{loc.file_name()};
        shortloc.remove_prefix(
            std::string_view(loc.file_name()).rfind(search_str)
            + search_str.length()
        );
        return std::format("{}:{} ", shortloc, loc.line());
    }
    return {};
}
} // namespace

void core::log::detail::logger(
    core::log::Level     level,
    std::string          text,
    std::source_location loc
) {
    if (logging_level <= level) {
        if (enable_source_loc) {
            std::println(
                std::cerr,
                "{:%T} [{}] {}- {}",
                std::chrono::system_clock::now(),
                to_string(level),
                std::format(
                    "{}:{} ",
                    shorten_name(loc.file_name()),
                    loc.line(),
                    loc.function_name()
                ),
                text
            );
        } else {
            std::println(
                std::cerr,
                "{:%T} [{}] {}",
                std::chrono::system_clock::now(),
                to_string(level),
                text
            );
        }
    }
}
