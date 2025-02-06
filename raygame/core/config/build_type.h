#pragma once

namespace core::config::detail {
consteval bool debug() {
#if defined(NDEBUG)
    return false;
#else
    return true;
#endif
}
} // namespace core::config::detail

#if defined(NDEBUG)
// NOLINTNEXTLINE(*-macro-usage)
#    define RAYGAME_RELEASE_ONLY(x) x
#    define RAYGAME_DEBUG_ONLY(x)
#else
// NOLINTNEXTLINE(*-macro-usage)
#    define RAYGAME_DEBUG_ONLY(x) x
#    define RAYGAME_RELEASE_ONLY(x)
#endif
