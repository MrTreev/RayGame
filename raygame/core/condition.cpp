#include "raygame/core/condition.h" // IWYU pragma: keep
#include "raygame/core/logger.h"
#include <string>
#include <utility>

namespace core::condition::detail {
void conditionlog(const std::string& message, const std::source_location& loc) {
    core::log::error(std::move(message), loc);
}
} // namespace core::condition::detail
