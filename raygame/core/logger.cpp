#include "raygame/core/logger.h" // IWYU pragma: keep
#include <chrono>
#include <iostream>
#include <source_location>
#include <string_view>

namespace {
#if defined(RAYGAME_ENABLE_SOURCE_LOC)
constexpr bool enable_source_loc = true;
#elif defined(RAYGAME_DISABLE_SOURCE_LOC)
constexpr bool enable_source_loc = false;
#else
#    warning "No source location macro defined, disabling"
constexpr bool enable_source_loc = false;
#endif

consteval size_t get_prefix_len(
    const std::source_location loc = std::source_location::current()
) {
    const std::string_view search_str = "/raygame/";
    const std::string_view locname    = loc.file_name();
    const size_t           nopref_len = locname.rfind(search_str);
    return nopref_len + search_str.length() + 2;
}

constexpr std::string_view shorten_name(std::string_view full_loc) {
    std::string_view shortloc(full_loc);
    shortloc.remove_prefix(get_prefix_len());
    return shortloc;
}

constexpr std::string
location_string([[maybe_unused]] const std::source_location& loc) {
    if (enable_source_loc) {
        return std::format(
            "{}:{}:{} ",
            shorten_name(loc.file_name()),
            loc.line(),
            loc.function_name()
        );
    }
    return {};
}

} // namespace

void core::log::detail::logger(
    const core::log::Level&     level,
    const std::string&          text,
    const std::source_location& loc
) {
    if (logging_level <= level) {
        std::println(
            std::cout,
            "{:%T} [{}] {}- {}",
            std::chrono::system_clock::now(),
            to_string(level),
            location_string(loc),
            text
        );
    }
}
