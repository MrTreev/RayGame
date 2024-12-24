#pragma once
#include "raygame/core/concepts.h"
#include "raygame/core/config.h"
#include "raygame/core/exception.h"
#include <format> // IWYU pragma: keep
#include <source_location>
#include <string>
#include <type_traits>

namespace core::condition {
namespace detail {
void conditionlog(const std::string& message, const std::source_location& loc);
}

//! Pre-Condition Checker
/*!
 *  @see PreCondition
 *  @throws core::exception::PreCondition If condition does not hold
 */
constexpr void pre_condition(
    const concepts::Checkable auto& check,
    const std::string&              message,
    const std::source_location&     loc = std::source_location::current()
) {
    using exception::PreCondition;
    if (!check) {
        if (!std::is_constant_evaluated()) {
            detail::conditionlog(message, loc);
        }
        throw PreCondition(message);
    }
}

//! Condition Checker
/*!
 *  @see CheckCondition
 *  @throws core::exception::CheckCondition If condition does not hold
 */
constexpr void check_condition(
    const concepts::Checkable auto& check,
    const std::string&              message,
    const std::source_location&     loc = std::source_location::current()
) {
    if (!check) {
        if (!std::is_constant_evaluated()) {
            detail::conditionlog(message, loc);
        }
        throw core::exception::CheckCondition(message);
    }
}

//! Post-Condition Checker
/*!
 *  @see PostCondition
 *  @throws core::exception::PostCondition If condition does not hold
 */
template<core::concepts::Checkable T>
constexpr void post_condition(
    const T&                    check,
    const std::string&          message,
    const std::source_location& loc = std::source_location::current()
) {
    if (!check) {
        if (!std::is_constant_evaluated()) {
            detail::conditionlog(message, loc);
        }
        throw core::exception::PostCondition(message);
    }
}

//! Null-Pointer Checker
/*!
 *  @see CheckCondition
 *  @throws core::exception::CheckCondition If pointer is null
 */
constexpr void check_ptr(
    const concepts::Pointer auto& check,
    const std::string&            message,
    const std::source_location&   loc = std::source_location::current()
) {
    if (check == nullptr) {
        if (!std::is_constant_evaluated()) {
            detail::conditionlog(message, loc);
        }
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
            ::core::condition::detail::conditionlog("Unknown " item_name);     \
        }                                                                      \
        static_assert(true)
#elif defined(RAYGAME_BUILD_TYPE_DEBUG)
#    define RAYGAME_ELSE_UNKNOWN(item_name)                                    \
        else {                                                                 \
            throw ::core::exception::Condition("Unknown " item_name);          \
        }                                                                      \
        static_assert(true)
#endif
