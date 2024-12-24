#include "core/base/condition.h" // IWYU pragma: keep
#include "core/base/logger.h"

namespace core::condition::detail {
void conditionlog(const std::string& message, const std::source_location& loc) {
    core::log::fatal(message, loc);
}
} // namespace core::condition::detail
