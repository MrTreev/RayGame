#pragma once
#include "core/exception.h"
#include <string>

namespace core::condition {

//! Pre-Condition Checker
/*!
 *  @see PreCondition
 */
constexpr void pre_condition(const bool& check, const std::string& message);

//! Condition Checker
/*!
 *  @see CheckCondition
 */
constexpr void check_condition(const bool& check, const std::string& message);

//! Post-Condition Checker
/*!
 *  @see PostCondition
 */
constexpr void post_condition(const bool& check, const std::string& message);

} // namespace core::condition

constexpr void
core::condition::pre_condition(const bool& check, const std::string& message) {
    if (!check) {
        throw core::exception::PreCondition(message);
    }
}

constexpr void core::condition::check_condition(
    const bool&        check,
    const std::string& message
) {
    if (!check) {
        throw core::exception::CheckCondition(message);
    }
}

constexpr void
core::condition::post_condition(const bool& check, const std::string& message) {
    if (!check) {
        throw core::exception::PostCondition(message);
    }
}
