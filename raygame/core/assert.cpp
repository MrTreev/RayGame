#include "raygame/core/assert.h"
#include "raygame/core/debug.h"
#include <cstdlib>
#include <iostream>
#include <print>

namespace core::detail {
void raygame_assert_raise(std::string_view msg, std::source_location loc) {
    std::println(std::cerr, "[{}] {}", debug::location_message(loc), msg);
    std::quick_exit(EXIT_FAILURE);
}
} // namespace core::detail
