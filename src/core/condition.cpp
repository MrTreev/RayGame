#include "core/condition.h"
#include "core/exception.h"

void core::condition::pre_condition(
    const bool&        check,
    const std::string& message
) {
    if (check) {
        throw core::exception::PreCondition(message);
    }
}

void core::condition::check_condition(
    const bool&        check,
    const std::string& message
) {
    if (check) {
        throw core::exception::CheckCondition(message);
    }
}

void core::condition::post_condition(
    const bool&        check,
    const std::string& message
) {
    if (check) {
        throw core::exception::PostCondition(message);
    }
}
