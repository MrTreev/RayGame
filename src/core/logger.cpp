#include "core/logger.h" // IWYU pragma: keep
#include <chrono>
#include <iostream>
#include <string_view>

#if defined(RAYGAME_LOG_LOCATION)
namespace {
consteval size_t get_prefix_len(
    const core::detail::source_location loc =
        core::detail::source_location::current()
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

const size_t start_time =
    static_cast<size_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch()
    )
                            .count());

} // namespace
#endif

void core::log::detail::logger(
    const core::log::Level& level,
    const std::string& text RG_LOC_DEF
) {
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    using std::chrono::duration_cast;
    using ms = std::chrono::milliseconds;

    const size_t time_ms =
        static_cast<size_t>(duration_cast<ms>(now).count()) - start_time;

    std::cout << time_ms << " - " << to_string(level)
#if defined(RAYGAME_LOG_LOCATION)
              << " - " << shorten_name(loc.file_name()) << ":" << loc.line()
              << ":" << loc.function_name()
#endif
              << " - " << text << "\n";
}

template<class... Args>
void core::log::detail::logger(
    const core::log::Level&     level,
    std::format_string<Args...> fmt,
    Args&&... args              RG_LOC_DEF
) {
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    using std::chrono::duration_cast;
    using ms = std::chrono::milliseconds;

    const size_t time_ms =
        static_cast<size_t>(duration_cast<ms>(now).count()) - start_time;

    const auto message = std::format(fmt, std::forward<Args...>(args)...);
    std::cout << time_ms << " - " << to_string(level)
#if defined(RAYGAME_LOG_LOCATION)
              << " - " << shorten_name(loc.file_name()) << ":" << loc.line()
              << ":" << loc.function_name()
#endif
              << " - " << message << "\n";
}
