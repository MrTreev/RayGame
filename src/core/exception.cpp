#include "core/exception.h"
#include <stdexcept>

core::exception::detail::Condition::Condition(const std::string& message)
    : ::std::logic_error(message) {}

core::exception::detail::Condition::Condition(const std::logic_error&& error)
    : ::std::logic_error(error) {}

core::exception::PreCondition::PreCondition(const std::string& message)
    : detail::Condition(message) {}

core::exception::CheckCondition::CheckCondition(const std::string& message)
    : detail::Condition(message){};

core::exception::PostCondition::PostCondition(const std::string& message)
    : detail::Condition(message){};
