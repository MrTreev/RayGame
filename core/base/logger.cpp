#include "core/base/logger.h" // IWYU pragma: keep
#include <chrono>
#include <iostream>
#include <ostream>
#include <source_location>
#include <string_view>

namespace {

consteval size_t get_prefix_len(
    const std::source_location loc = std::source_location::current()
) {
    const std::string_view search_str = "/src/";
    const std::string_view locname    = loc.file_name();
    const size_t           nopref_len = locname.rfind(search_str);
    return nopref_len + search_str.length();
}

constexpr std::string_view shorten_name(std::string_view full_loc) {
    std::string_view shortloc(full_loc);
    shortloc.remove_prefix(get_prefix_len());
    return shortloc;
}

constexpr std::string location_string(const std::source_location& loc) {
    return std::format(
        "{}:{}:{} ",
        shorten_name(loc.file_name()),
        loc.line(),
        loc.function_name()
    );
}

} // namespace

void core::log::detail::logger(
    const core::log::Level&     level,
    const std::source_location& loc,
    const std::string&          text
) {
    if (logging_level <= level) {
        std::println(
            std::cout,
            "{:%T} [{}] {} - {}",
            std::chrono::zoned_time{
                std::chrono::current_zone(),
                std::chrono::system_clock::now()
            },
            to_string(level),
            location_string(loc),
            text
        );
    }
}

void core::log::detail::logger(
    const core::log::Level& level,
    const std::string&      text
) {
    if (logging_level <= level) {
        std::println(
            std::cout,
            "{:%T} [{}] - {}",
            std::chrono::zoned_time{
                std::chrono::current_zone(),
                std::chrono::system_clock::now()
            },
            to_string(level),
            text
        );
    }
}
