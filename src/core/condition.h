#pragma once
#include <string>

namespace core::condition {

//! Pre-Condition Checker
/*!
 *  @see PreCondition
 */
void pre_condition(const bool& check, const std::string& message);

//! Condition Checker
/*!
 *  @see CheckCondition
 */
void check_condition(const bool& check, const std::string& message);

//! Post-Condition Checker
/*!
 *  @see PostCondition
 */
void post_condition(const bool& check, const std::string& message);

} // namespace core::condition
