#include "raygame/core/base/exception.h" // IWYU pragma: keep

core::exception::Exception::Exception(const std::string& message)
    : ::std::runtime_error(message) {}

core::exception::Exception::Exception(const std::runtime_error&& error)
    : ::std::runtime_error(error) {}

core::exception::Condition::Condition(const std::string& message)
    : core::exception::Exception(message) {}

core::exception::PreCondition::PreCondition(const std::string& message)
    : Condition(message) {}

core::exception::CheckCondition::CheckCondition(const std::string& message)
    : Condition(message) {}

core::exception::PostCondition::PostCondition(const std::string& message)
    : Condition(message) {}

core::exception::Exception::~Exception()           = default;
core::exception::Condition::~Condition()           = default;
core::exception::PreCondition::~PreCondition()     = default;
core::exception::CheckCondition::~CheckCondition() = default;
core::exception::PostCondition::~PostCondition()   = default;
