#pragma once
#include "core/exception.h"
#include "core/logger.h"
#include <string>

namespace core::condition {

//! Pre-Condition Checker
/*!
 *  @see PreCondition
 */
inline constexpr void pre_condition(
    const bool&                          check,
    const std::string&                   message,
    const core::detail::source_location& loc
);

//! Condition Checker
/*!
 *  @see CheckCondition
 */
inline constexpr void check_condition(
    const bool&                          check,
    const std::string&                   message,
    const core::detail::source_location& loc
);

//! Post-Condition Checker
/*!
 *  @see PostCondition
 */
inline constexpr void post_condition(
    const bool&                          check,
    const std::string&                   message,
    const core::detail::source_location& loc
);

} // namespace core::condition

inline constexpr void core::condition::pre_condition(
    const bool&                          check,
    const std::string&                   message,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    if (!check) {
        core::log::fatal(message, loc);
        throw core::exception::PreCondition(message);
    }
}

inline constexpr void core::condition::check_condition(
    const bool&                          check,
    const std::string&                   message,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    if (!check) {
        core::log::fatal(message, loc);
        throw core::exception::CheckCondition(message);
    }
}

inline constexpr void core::condition::post_condition(
    const bool&                          check,
    const std::string&                   message,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    if (!check) {
        core::log::fatal(message, loc);
        throw core::exception::PostCondition(message);
    }
}
