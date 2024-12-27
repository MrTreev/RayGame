#pragma once
#include "raygame/core/types.h"
#include <format>
#include <source_location>
#include <string>
#include <utility>

namespace core::log {

//! Logging level
enum class Level : uint8_t {
    TRACE    = 0,
    DEBUG    = 10,
    INFO     = 20,
    NOTE     = 30,
    PROGRESS = 40,
    /* 50 - 80 */
    WARNING  = 80,
    ERROR    = 90,
    FATAL    = 255,
};

#if defined(RAYGAME_LOG_TRACE)
constexpr Level logging_level = Level::TRACE;
#elif defined(RAYGAME_LOG_DEBUG)
constexpr Level logging_level = Level::DEBUG;
#elif defined(RAYGAME_LOG_INFO)
constexpr Level logging_level = Level::INFO;
#elif defined(RAYGAME_LOG_NOTE)
constexpr Level logging_level = Level::NOTE;
#elif defined(RAYGAME_LOG_PROGRESS)
constexpr Level logging_level = Level::PROGRESS;
#elif defined(RAYGAME_LOG_WARNING)
constexpr Level logging_level = Level::WARNING;
#elif defined(RAYGAME_LOG_ERROR)
constexpr Level logging_level = Level::ERROR;
#elif defined(RAYGAME_LOG_FATAL)
constexpr Level logging_level = Level::FATAL;
#else
#    warning "No logging level set for RAYGAME, using NOTE"
constexpr Level logging_level = Level::NOTE;
#endif

//! Logging level to string converter
constexpr std::string to_string(Level level) {
    switch (level) {
    case Level::TRACE:
        return "TRACE";
    case Level::DEBUG:
        return "DEBUG";
    case Level::INFO:
        return "INFO ";
    case Level::NOTE:
        return "NOTE ";
    case Level::PROGRESS:
        return "PROG ";
    case Level::WARNING:
        return "WARN ";
    case Level::ERROR:
        return "ERROR";
    case Level::FATAL:
        return "FATAL";
    }
    std::unreachable();
}

namespace detail {
void logger(
    const core::log::Level&     level,
    const std::string&          text,
    const std::source_location& loc = std::source_location::current()
);
} // namespace detail

template<typename... Args>
struct trace {
    constexpr trace(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::TRACE, message, loc);
    }

    constexpr trace(
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
    constexpr debug(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::DEBUG, message, loc);
    }

    constexpr debug(
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
    constexpr info(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::INFO, message, loc);
    }

    constexpr info(
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
    constexpr note(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::NOTE, message, loc);
    }

    constexpr note(
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
    constexpr progress(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::PROGRESS, message, loc);
    }

    constexpr progress(
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
    constexpr warning(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::WARNING, message, loc);
    }

    constexpr warning(
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
    constexpr error(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::ERROR, message, loc);
    }

    constexpr error(
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
    constexpr fatal(
        const std::string&          message,
        const std::source_location& loc = std::source_location::current()
    ) {
        detail::logger(Level::FATAL, message, loc);
    }

    constexpr fatal(
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

} // namespace core::log
