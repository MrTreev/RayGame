#pragma once
#include "raygame/core/concepts.h"
#include "raygame/core/config.h"
#include "raygame/core/exception.h"
#include "raygame/core/logger.h"
#include <source_location>
#include <string>
#include <type_traits>
#include <utility>

namespace core::condition {

//! Pre-Condition Checker
/*!
 *  @see PreCondition
 *  @throws core::exception::PreCondition If condition does not hold
 */
template<typename... Args>
constexpr void pre_condition(
    const concepts::Checkable auto& check,
    std::format_string<Args...>     fmt,
    Args&&... args,
    std::source_location loc = std::source_location::current()
) noexcept(false) {
    using exception::PreCondition;
    if (!check) {
        if (!std::is_constant_evaluated()) {
            log::error(fmt, std::forward<Args>(args)..., loc);
        }
        throw PreCondition(std::format(fmt, std::forward<Args>(args)...));
    }
}

//! Condition Checker
/*!
 *  @see CheckCondition
 *  @throws core::exception::CheckCondition If condition does not hold
 */
template<typename... Args>
constexpr void check_condition(
    const concepts::Checkable auto& check,
    std::format_string<Args...>     fmt,
    Args&&... args,
    std::source_location loc = std::source_location::current()
) noexcept(false) {
    if (!check) {
        if (!std::is_constant_evaluated()) {
            log::error(fmt, std::forward<Args>(args)..., loc);
        }
        throw exception::CheckCondition(
            std::format(fmt, std::forward<Args>(args)...)
        );
    }
}

//! Post-Condition Checker
/*!
 *  @see PostCondition
 *  @throws core::exception::PostCondition If condition does not hold
 */
template<typename... Args>
constexpr void post_condition(
    const core::concepts::Checkable auto& check,
    std::format_string<Args...>           fmt,
    Args&&... args,
    std::source_location loc = std::source_location::current()
) noexcept(false) {
    if (!check) {
        if (!std::is_constant_evaluated()) {
            log::error(fmt, std::forward<Args>(args)..., loc);
        }
        throw exception::PostCondition(
            std::format(fmt, std::forward<Args>(args)..., loc)
        );
    }
}

//! Null-Pointer Checker
/*!
 *  @see CheckCondition
 *  @throws core::exception::CheckCondition If pointer is null
 */
template<typename... Args>
constexpr void check_ptr(
    const concepts::Pointer auto& check,
    std::format_string<Args...>   fmt,
    Args&&... args,
    std::source_location loc = std::source_location::current()
) noexcept(false) {
    if (check == nullptr) {
        if (!std::is_constant_evaluated()) {
            log::error(fmt, std::forward<Args>(args)..., loc);
        }
        throw exception::CheckCondition(
            std::format(fmt, std::forward<Args>(args)..., loc)
        );
    }
}

//! Function to mark an unknown case
/*!
 *  @throws core::exception::Condition If hit
 */
template<typename... Args>
RAYGAME_DEBUG_ONLY([[noreturn]]
)

constexpr void unknown(
    std::format_string<Args...> fmt,
    Args&&... args,
    std::source_location loc = std::source_location::current()
) {
    if constexpr (config::BUILD_TYPE == config::BuildType::RELEASE) {
        log::error(fmt, std::forward<Args>(args)..., loc);
    } else {
        throw exception::UnknownCase(
            std::format(fmt, std::forward<Args>(args)..., loc)
        );
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
        constexpr std::string msg{"Reached block marked unreachable"};
        log::error(loc, msg);
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
        log::error("Reached block marked unimplemented", loc);
    } else {
        throw exception::Unimplemented("Unimplemented");
    }
}

} // namespace core::condition
