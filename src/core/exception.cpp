#include "core/exception.h" // IWYU pragma: keep

core::exception::Condition::Condition(const std::string& message)
    : ::std::logic_error(message) {}

core::exception::Condition::Condition(const std::logic_error&& error)
    : ::std::logic_error(error) {}

core::exception::PreCondition::PreCondition(const std::string& message)
    : Condition(message) {}

core::exception::CheckCondition::CheckCondition(const std::string& message)
    : Condition(message) {}

core::exception::PostCondition::PostCondition(const std::string& message)
    : Condition(message) {}

core::exception::Condition::~Condition()           = default;
core::exception::PreCondition::~PreCondition()     = default;
core::exception::CheckCondition::~CheckCondition() = default;
core::exception::PostCondition::~PostCondition()   = default;
