#pragma once

//=============================================================================
// Assertion
//=============================================================================
#if !defined(RAYGAME_ASSERT)
#    include <source_location>
#    include <string_view>

namespace core::detail {
[[noreturn]]
void raygame_assert_raise(std::string_view msg, std::source_location loc);

constexpr void raygame_assert(
    auto                   condition,
    const std::string_view msg = "",
    std::source_location   loc = std::source_location::current()
) {
    if (condition) {
        raygame_assert_raise(msg, loc);
    }
}

} // namespace core::detail

#    if defined(RAYGAME_RAYTEST)
#        include "raytest/raytest.h"
// NOLINTNEXTLINE(*-macro-usage)
#        define RAYGAME_ASSERT(condition, ...) RG_CHECK_TRUE(condition)
#    else
// NOLINTNEXTLINE(*-macro-usage)
#        define RAYGAME_ASSERT(condition, ...)                                                     \
            ::core::detail::raygame_assert(condition __VA_OPT__(, ) __VA_ARGS__)
#    endif

#endif
