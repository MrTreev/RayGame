#pragma once
#include "core/exception.h"
#include "core/logger.h"
#include <string>

namespace core::condition {

//! Pre-Condition Checker
/*!
 *  @see PreCondition
 */
inline constexpr void
pre_condition(const bool& check, const std::string& message RG_LOC_DEF);

//! Condition Checker
/*!
 *  @see CheckCondition
 */
inline constexpr void
check_condition(const bool& check, const std::string& message RG_LOC_DEF);

//! Post-Condition Checker
/*!
 *  @see PostCondition
 */
inline constexpr void
post_condition(const bool& check, const std::string& message RG_LOC_DEF);

} // namespace core::condition

inline constexpr void core::condition::pre_condition(
    const bool&                check,
    const std::string& message RG_LOC_CUR
) {
    if (!check) {
        core::log::fatal(message RG_LOC_VAR);
        throw core::exception::PreCondition(message);
    }
}

inline constexpr void core::condition::check_condition(
    const bool&                check,
    const std::string& message RG_LOC_CUR
) {
    if (!check) {
        core::log::fatal(message RG_LOC_VAR);
        throw core::exception::CheckCondition(message);
    }
}

inline constexpr void core::condition::post_condition(
    const bool&                check,
    const std::string& message RG_LOC_CUR
) {
    if (!check) {
        core::log::fatal(message RG_LOC_VAR);
        throw core::exception::PostCondition(message);
    }
}
