#pragma once
#include "raygame/core/config.h"
#include <format>
#include <source_location>
#include <string>

namespace core::log {
//! Logging level to string converter
namespace detail {
void logger(
    const core::log::Level&     level,
    const std::string&          text,
    const std::source_location& loc
);
} // namespace detail

// NOLINTBEGIN(*-avoid-c-arrays)
template<typename... Args>
struct trace {
    constexpr explicit trace(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::TRACE, message, loc);
    }

    constexpr explicit trace(
        std::format_string<Args...> fmt,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    )
        : trace(std::vformat(fmt.get(), std::make_format_args(args...)), loc) {}
};

template<typename... Args>
trace(Args&&...) -> trace<Args...>;
template<typename... Args>
trace(const char[]) -> trace<std::string>;
template<typename... Args>
trace(const char[], Args&&...) -> trace<Args...>;

template<typename... Args>
struct debug {
    constexpr explicit debug(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::DEBUG, message, loc);
    }

    constexpr explicit debug(
        std::format_string<Args...> fmt,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    )
        : debug(std::vformat(fmt.get(), std::make_format_args(args...)), loc) {}
};

template<typename... Args>
debug(Args&&...) -> debug<Args...>;
template<typename... Args>
debug(const char[]) -> debug<std::string>;
template<typename... Args>
debug(const char[], Args&&...) -> debug<Args...>;

template<typename... Args>
struct info {
    constexpr explicit info(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::INFO, message, loc);
    }

    constexpr explicit info(
        std::format_string<Args...> fmt,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    )
        : info(std::vformat(fmt.get(), std::make_format_args(args...)), loc) {}
};

template<typename... Args>
info(Args&&...) -> info<Args...>;
template<typename... Args>
info(const char[]) -> info<std::string>;
template<typename... Args>
info(const char[], Args&&...) -> info<Args...>;

template<typename... Args>
struct note {
    constexpr explicit note(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::NOTE, message, loc);
    }

    constexpr explicit note(
        std::format_string<Args...> fmt,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    )
        : note(std::vformat(fmt.get(), std::make_format_args(args...)), loc) {}
};

template<typename... Args>
note(Args&&...) -> note<Args...>;
template<typename... Args>
note(const char[]) -> note<std::string>;
template<typename... Args>
note(const char[], Args&&...) -> note<Args...>;

template<typename... Args>
struct progress {
    constexpr explicit progress(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::PROGRESS, message, loc);
    }

    constexpr explicit progress(
        std::format_string<Args...> fmt,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    )
        : progress(
              std::vformat(fmt.get(), std::make_format_args(args...)),
              loc
          ) {}
};

template<typename... Args>
progress(Args&&...) -> progress<Args...>;
template<typename... Args>
progress(const char[]) -> progress<std::string>;
template<typename... Args>
progress(const char[], Args&&...) -> progress<Args...>;

template<typename... Args>
struct warning {
    constexpr explicit warning(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::WARNING, message, loc);
    }

    constexpr explicit warning(
        std::format_string<Args...> fmt,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    )
        : warning(
              std::vformat(fmt.get(), std::make_format_args(args...)),
              loc
          ) {}
};

template<typename... Args>
warning(Args&&...) -> warning<Args...>;
template<typename... Args>
warning(const char[]) -> warning<std::string>;
template<typename... Args>
warning(const char[], Args&&...) -> warning<Args...>;

template<typename... Args>
struct error {
    constexpr explicit error(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::ERROR, message, loc);
    }

    constexpr explicit error(
        std::format_string<Args...> fmt,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    )
        : error(std::vformat(fmt.get(), std::make_format_args(args...)), loc) {}
};

template<typename... Args>
error(Args&&...) -> error<Args...>;
template<typename... Args>
error(const char[]) -> error<std::string>;
template<typename... Args>
error(const char[], Args&&...) -> error<Args...>;

template<typename... Args>
struct fatal {
    constexpr explicit fatal(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::FATAL, message, loc);
    }

    constexpr explicit fatal(
        std::format_string<Args...> fmt,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    )
        : fatal(std::vformat(fmt.get(), std::make_format_args(args...)), loc) {}
};

template<typename... Args>
fatal(Args&&...) -> fatal<Args...>;
template<typename... Args>
fatal(const char[]) -> fatal<std::string>;
template<typename... Args>
fatal(const char[], Args&&...) -> fatal<Args...>;

// NOLINTEND(*-avoid-c-arrays)
} // namespace core::log
