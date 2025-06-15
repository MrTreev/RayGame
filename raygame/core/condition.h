#pragma once
#include "raygame/core/concepts.h"
#include "raygame/core/config.h"
#include "raygame/core/exception.h"
#include <format>
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
    bool                        check,
    const std::string&          message,
    const std::source_location& loc = std::source_location::current()
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
        throw exception::CheckCondition(message);
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
        throw exception::PostCondition(message);
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
        throw exception::CheckCondition(message);
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
[[noreturn]]
constexpr void unknown(
    const std::string&          name,
    const std::source_location& loc = std::source_location::current()
) {
    if constexpr (config::BUILD_TYPE == config::BuildType::DEBUG) {
        detail::conditionlog("Unknown " + name, loc);
    }
    throw exception::UnknownCase("Unknown " + name);
}

//! Function to mark an unreachable code block
/*!
 *  @throws core::exception::Condition If hit
 */
[[noreturn]]
constexpr void unreachable(const std::source_location& loc = std::source_location::current()) {
    if constexpr (config::BUILD_TYPE == config::BuildType::DEBUG) {
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
constexpr void unimplemented(const std::source_location& loc = std::source_location::current()) {
    if constexpr (config::BUILD_TYPE == config::BuildType::DEBUG) {
        detail::conditionlog("Reached block marked unimplemented", loc);
    }
    throw exception::Unimplemented("Unimplemented");
}

//! Pre-Condition Check value not less than min
/*!
 *  @param  val value
 *  @throws core::exception::PreCondition If @p val is less than min
 */
void pre_check_min(
    const std::integral auto    val,
    const std::integral auto    min,
    const std::source_location& loc = std::source_location::current()
) {
    pre_condition(
        std::cmp_greater_equal(val, min),
        std::format(
            "Pre-Condition failed: Minimum check\n"
            "\tGot: {}\n"
            "\tMin: {}",
            val,
            min
        ),
        loc
    );
}

//! Pre-Condition Check value is not greater than max
/*!
 *  @throws core::exception::PreCondition If @p val is greater than max
 */
void pre_check_max(
    const std::integral auto    val,
    const std::integral auto    max,
    const std::source_location& loc = std::source_location::current()
) {
    pre_condition(
        std::cmp_less_equal(val, max),
        std::format(
            "Pre-Condition failed: Maximum check\n"
            "\tGot: {}\n"
            "\tMax: {}",
            val,
            max
        ),
        loc
    );
}

//! Pre-Condition Check value is within range
/*!
 *  @throws core::exception::PreCondition If @p val is outside of range
 */
void pre_check_range(
    const std::integral auto    val,
    const std::integral auto    min,
    const std::integral auto    max,
    const std::source_location& loc = std::source_location::current()
) {
    pre_condition(
        std::cmp_greater_equal(val, min) && std::cmp_less_equal(val, max),
        std::format(
            "Pre-Condition failed: Range check\n"
            "\tGot: {}\n"
            "\tMin: {}\n"
            "\tMax: {}",
            val,
            min,
            max
        ),
        loc
    );
}

} // namespace core::condition
