#include "core/logger.h"
#include "config.h"
#include <chrono>
#include <iostream>
#include <string_view>

namespace {
constexpr std::string_view shorten_name(std::string_view full_loc) {
    std::string_view shortloc(full_loc);
    shortloc.remove_prefix(config::path_count);
    return shortloc;
}
} // namespace

void core::log::detail::logger(
    const core::log::Level& level,
    const std::string&      text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const source_location& loc
#endif
) {
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    using std::chrono::duration_cast;
    using ms = std::chrono::milliseconds;

    const auto time_ms = duration_cast<ms>(now).count() - config::start_time;

    std::cout << time_ms << " - " << to_string(level)
#if defined(RAYGAME_LOG_LOCATION)
              << " - " << shorten_name(loc.file_name()) << ":" << loc.line()
              << ":" << loc.function_name()
#endif
              << " - " << text << "\n";
}
