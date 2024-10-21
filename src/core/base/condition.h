#pragma once
#include "core/base/exception.h"
#include "core/base/logger.h"
#include <string>

// Keep for macro
#include <format> // IWYU pragma: keep

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

#define RAYGAME_PRE_CONDITION(expr)  ::core::condition::pre_condition((expr), #expr)
#define RAYGAME_POST_CONDITION(expr) ::core::condition::post_condition((expr), #expr)
#define RAYGAME_CHECK_CONDITION(expr)                                               \
    ::core::condition::check_condition((expr), #expr)
#define RAYGAME_PRE_CONDITION_MSG(expr, ...)                                        \
    ::core::condition::pre_condition((expr), std::format(__VA_ARGS__))
#define RAYGAME_POST_CONDITION_MSG(expr, ...)                                       \
    ::core::condition::post_condition((expr), std::format(__VA_ARGS__))
#define RAYGAME_CHECK_CONDITION_MSG(expr, ...)                                      \
    ::core::condition::check_condition((expr), std::format(__VA_ARGS__))

#if defined(RAYGAME_BUILD_TYPE_RELEASE)
#    define RAYGAME_ELSE_UNKNOWN(item_name)                                         \
        else {                                                                 \
            ::core::log::debug("Unknown " item_name);                          \
        }                                                                      \
        static_assert(true)
#elif defined(RAYGAME_BUILD_TYPE_DEBUG)
#    define RAYGAME_ELSE_UNKNOWN(item_name)                                         \
        else {                                                                 \
            throw ::core::exception::Condition("Unknown " item_name);          \
        }                                                                      \
        static_assert(true)
#endif
