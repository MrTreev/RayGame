#pragma once
#include "core/exception.h"
#include "core/logger.h"
#include <string>

namespace core::condition {

namespace detail {
template<typename T>
concept checkable = requires(T t) { !t; };
} // namespace detail

//! Pre-Condition Checker
/*!
 *  @see PreCondition
 */
template<typename Checkable_T>
requires detail::checkable<Checkable_T>
inline constexpr void pre_condition(
    const Checkable_T&                   check,
    const std::string&                   message,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    if (!check) {
        core::log::fatal(message, loc);
        throw core::exception::PreCondition(message);
    }
}

//! Condition Checker
/*!
 *  @see CheckCondition
 */
template<typename Checkable_T>
requires detail::checkable<Checkable_T>
inline constexpr void check_condition(
    const Checkable_T&                   check,
    const std::string&                   message,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    if (!check) {
        core::log::fatal(message, loc);
        throw core::exception::CheckCondition(message);
    }
}

//! Post-Condition Checker
/*!
 *  @see PostCondition
 */
template<typename Checkable_T>
requires detail::checkable<Checkable_T>
inline constexpr void post_condition(
    const Checkable_T&                   check,
    const std::string&                   message,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    if (!check) {
        core::log::fatal(message, loc);
        throw core::exception::PostCondition(message);
    }
}

//! Null ptr checker
/*!
 *  @see CheckCondition
 */
template<typename T>
inline constexpr void check_ptr(
    const T&                             check,
    const std::string&                   message,
    const core::detail::source_location& loc =
        core::detail::source_location::current()
) {
    static_assert(std::is_pointer_v<T>);
    if (check == nullptr) {
        core::log::fatal(message, loc);
        throw core::exception::CheckCondition(message);
    }
}

} // namespace core::condition
