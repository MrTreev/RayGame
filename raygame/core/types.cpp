#include "raygame/core/types.h" // IWYU pragma: keep
#include <source_location>

namespace {
enum class SourceLoc : uint8_t {
    NONE = 0,
    FULL,
    BASE,
};
#if defined(RAYGAME_SOURCE_LOCATION_FULL)
constexpr SourceLoc sloc_type = SourceLoc::FULL;
#elif defined(RAYGAME_SOURCE_LOCATION_BASE)
constexpr SourceLoc sloc_type = SourceLoc::BASE;
#elif defined(RAYGAME_SOURCE_LOCATION_NONE)
constexpr SourceLoc sloc_type = SourceLoc::NONE;
#else
#    warning "No source location macro defined, disabling"
constexpr SourceLoc sloc_type = SourceLoc::BASE;
#endif
} // namespace

consteval size_t repo_dir_pref() {
    const auto        loc{std::source_location::current()};
    const std::string subloc = "raygame/core/types.cpp";
    const std::string short_loc(loc.file_name());
    return short_loc.length() - subloc.length();
}

namespace core::debug {

std::string location_message(std::source_location loc) {
    if constexpr (sloc_type == SourceLoc::NONE) {
        return {};
    } else if constexpr (sloc_type == SourceLoc::BASE) {
        const std::string search_str{"/"};
        std::string_view  shortloc{loc.file_name()};
        shortloc.remove_prefix(
            std::string_view(loc.file_name()).rfind(search_str) + search_str.length()
        );
        return std::format("{}:{}", shortloc, loc.line());
    } else {
        std::string_view shortloc{loc.file_name()};
        const auto       preflen = repo_dir_pref();
        shortloc.remove_prefix(preflen);
        return std::format("{}:{}", shortloc, loc.line());
    }
}
} // namespace core::debug
