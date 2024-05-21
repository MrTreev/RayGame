#include "core/logger.h"
#include <chrono>
#include <iostream>

void core::log::detail::logger(
    const core::log::Level& level,
    const std::string&      text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const source_location& loc
#endif
) {
    using std::chrono::duration_cast;
    using ms = std::chrono::milliseconds;
    using sc = std::chrono::system_clock;
    const auto time_ms =
        duration_cast<ms>(sc::now().time_since_epoch()).count();
    std::cout << time_ms << "-" << to_string(level)
#if defined(RAYGAME_LOG_LOCATION)
              << "-" << loc.file_name() << ":" << loc.line()
#endif
              << "-" << text << "\n";
}
