#include "core/conditions.h"

void core::conditions::pre_condition(bool check, const std::string& message) {
    if (check) {
        throw core::exception::PreCondition(message);
    }
}

void core::conditions::check_condition(bool check, const std::string& message) {
    if (check) {
        throw core::exception::CheckCondition(message);
    }
}

void core::conditions::post_condition(bool check, const std::string& message) {
    if (check) {
        throw core::exception::PostCondition(message);
    }
}
