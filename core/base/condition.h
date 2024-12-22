#pragma once
#include "core/base/concepts.h"
#include "core/base/exception.h"
#include "core/base/logger.h"
#include <format> // IWYU pragma: keep
#include <source_location>
#include <string>

namespace core::condition {

//! Pre-Condition Checker
/*!
 *  @see PreCondition
 *  @throws core::exception::PreCondition If condition does not hold
 */
constexpr void pre_condition(
    const concepts::checkable auto& check,
    const std::string&              message,
    const std::source_location&     loc = std::source_location::current()
) {
    using exception::PreCondition;
    if (!check) {
        core::log::fatal(message, loc);
        throw PreCondition(message);
    }
}

//! Condition Checker
/*!
 *  @see CheckCondition
 *  @throws core::exception::CheckCondition If condition does not hold
 */
constexpr void check_condition(
    const concepts::checkable auto& check,
    const std::string&              message,
    const std::source_location&     loc = std::source_location::current()
) {
    if (!check) {
        core::log::fatal(message, loc);
        throw core::exception::CheckCondition(message);
    }
}

//! Post-Condition Checker
/*!
 *  @see PostCondition
 *  @throws core::exception::PostCondition If condition does not hold
 */
template<core::concepts::checkable T>
constexpr void post_condition(
    const T&                    check,
    const std::string&          message,
    const std::source_location& loc = std::source_location::current()
) {
    if (!check) {
        core::log::fatal(message, loc);
        throw core::exception::PostCondition(message);
    }
}

//! Null-Pointer Checker
/*!
 *  @see CheckCondition
 *  @throws core::exception::CheckCondition If pointer is null
 */
constexpr void check_ptr(
    const concepts::pointer auto& check,
    const std::string&            message,
    const std::source_location&   loc = std::source_location::current()
) {
    if (check == nullptr) {
        core::log::fatal(message, loc);
        throw core::exception::CheckCondition(message);
    }
}

} // namespace core::condition

#define RAYGAME_PRE_CONDITION(expr)                                            \
    ::core::condition::pre_condition((expr), #expr)
#define RAYGAME_POST_CONDITION(expr)                                           \
    ::core::condition::post_condition((expr), #expr)
#define RAYGAME_CHECK_CONDITION(expr)                                          \
    ::core::condition::check_condition((expr), #expr)
#define RAYGAME_PRE_CONDITION_MSG(expr, ...)                                   \
    ::core::condition::pre_condition((expr), std::format(__VA_ARGS__))
#define RAYGAME_POST_CONDITION_MSG(expr, ...)                                  \
    ::core::condition::post_condition((expr), std::format(__VA_ARGS__))
#define RAYGAME_CHECK_CONDITION_MSG(expr, ...)                                 \
    ::core::condition::check_condition((expr), std::format(__VA_ARGS__))

#if defined(RAYGAME_BUILD_TYPE_RELEASE)
#    define RAYGAME_ELSE_UNKNOWN(item_name)                                    \
        else {                                                                 \
            ::core::log::debug("Unknown " item_name);                          \
        }                                                                      \
        static_assert(true)
#elif defined(RAYGAME_BUILD_TYPE_DEBUG)
#    define RAYGAME_ELSE_UNKNOWN(item_name)                                    \
        else {                                                                 \
            throw ::core::exception::Condition("Unknown " item_name);          \
        }                                                                      \
        static_assert(true)
#endif
