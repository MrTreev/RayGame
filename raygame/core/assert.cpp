#include "raygame/core/assert.hpp"
#include "raygame/core/types.hpp"
#include <cstdlib>
#include <iostream>
#include <print>
#include <source_location>
#include <string_view>

namespace core::detail {
[[maybe_unused]]
void raygame_assert_raise(std::string_view msg, std::source_location loc) {
    std::println(std::cerr, "[{}] {}", debug::location_message(loc), msg);
    std::quick_exit(EXIT_FAILURE);
}
} // namespace core::detail
