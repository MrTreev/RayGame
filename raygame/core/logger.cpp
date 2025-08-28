#include "raygame/core/logger.h" // IWYU pragma: keep
#include "raygame/core/condition.h"
#include <chrono>
#include <iostream>
#include <source_location>
#include <string_view>

namespace {
enum class SourceLoc : uint8_t {
    NONE = 0,
    FULL,
    BASE,
};
#if defined(RAYGAME_ENABLE_SOURCE_LOCATION)
constexpr SourceLoc sloc_type = SourceLoc::FULL;
#elif defined(RAYGAME_DISABLE_SOURCE_LOCATION)
constexpr SourceLoc sloc_type = SourceLoc::BASE;
#else
#    warning "No source location macro defined, disabling"
constexpr bool sloc_type = false;
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
} // namespace

void core::log::detail::logger(core::log::Level level, std::string text, std::source_location loc) {
    if (logging_level <= level) {
        if constexpr (sloc_type == SourceLoc::NONE) {
            std::println(
                std::cerr,
                "{:%T} [{}] - {}",
                std::chrono::system_clock::now(),
                to_string(level),
                text
            );
        } else {
            constexpr std::string_view search_str = []() {
                if constexpr (sloc_type == SourceLoc::FULL) {
                    return "/raygame/";
                } else {
                    return "/";
                }
            }();
            std::string_view shortloc{loc.file_name()};
            shortloc.remove_prefix(
                std::string_view(loc.file_name()).rfind(search_str) + search_str.length()
            );
            std::println(
                std::cerr,
                "{:%T} [{}] {} - {}",
                std::chrono::system_clock::now(),
                to_string(level),
                std::format("{}:{}", shortloc, loc.line()),
                text
            );
        }
    }
}
