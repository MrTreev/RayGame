#include "raygame/core/condition.h" // IWYU pragma: keep
#include "raygame/core/logger.h"

namespace core::condition::detail {
void conditionlog(std::string message, std::source_location loc) {
    core::log::error(std::move(message), loc);
}
} // namespace core::condition::detail
