#pragma once
#include "raygame/core/concepts.h"
#include "raygame/core/config.h"
#include "raygame/core/exception.h"
#include <source_location>
#include <string>
#include <utility>

namespace core::condition {
namespace detail {
void conditionlog(std::string message, std::source_location loc);
} // namespace detail

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
    if (!check) {
        if (!std::is_constant_evaluated()) {
            detail::conditionlog(message, loc);
        }
        throw exception::PreCondition(message);
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

constexpr auto check_ret(
    concepts::Pointer auto      check,
    const std::string&          message,
    const std::source_location& loc = std::source_location::current()
) -> decltype(check) {
    check_ptr(check, message, loc);
    return check;
}

//! Function to mark an unknown case
/*!
 *  @throws core::exception::Condition If hit
 */
RAYGAME_DEBUG_ONLY([[noreturn]])

constexpr void unknown(
    const std::string&          name,
    const std::source_location& loc = std::source_location::current()
) {
    if constexpr (config::BUILD_TYPE == config::BuildType::RELEASE) {
        detail::conditionlog("Unknown " + name, loc);
    } else {
        throw exception::UnknownCase("Unknown " + name);
    }
}

//! Function to mark an unreachable code block
/*!
 *  @throws core::exception::Condition If hit
 */
[[noreturn]]
constexpr void
unreachable(const std::source_location& loc = std::source_location::current()) {
    if constexpr (config::BUILD_TYPE == config::BuildType::RELEASE) {
        detail::conditionlog("Reached block marked unreachable", loc);
        throw exception::Unreachable("Reached block marked unreachable");
    } else {
        std::unreachable();
    }
}

//! Function to mark an unimplemented code block
/*!
 *  @throws core::exception::Condition If hit
 */
[[noreturn]]
constexpr void unimplemented(
    const std::source_location& loc = std::source_location::current()
) {
    if constexpr (config::BUILD_TYPE == config::BuildType::RELEASE) {
        detail::conditionlog("Reached block marked unimplemented", loc);
    } else {
        throw exception::Unimplemented("Unimplemented");
    }
}

} // namespace core::condition
