#include "core/utils/logger.h"
#include <chrono>
#include <iostream>

void core::utils::detail::logger(
    const utils::Level& level,
    const std::string&  text
#if defined(RAYGAME_LOG_LOCATION)
    ,
    const source_location loc = source_location::current()
#endif
) {
    const auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::system_clock::now().time_since_epoch()
    )
                             .count();
    std::cerr << time_ms << "-" << to_string(level)
#if defined(RAYGAME_LOG_LOCATION)
              << "-" << loc.file_name() << ":" << loc.line()
#endif
              << "-" << text << "\n";
}
