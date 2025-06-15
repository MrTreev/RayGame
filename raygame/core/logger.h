#pragma once
#include "raygame/core/config.h"
#include <format>
#include <source_location>
#include <string>

namespace core::log {
//! Logging level to string converter
namespace detail {
void logger(core::log::Level level, std::string text, std::source_location loc);
} // namespace detail

// Makes it easier to have a single definition
// NOLINTNEXTLINE(*-macro-usage)
#define RG_LOG_STRUCT(level, LEVEL)                                                                \
    template<typename... Args>                                                                     \
    struct level {                                                                                 \
        constexpr explicit level(                                                                  \
            std::string          message,                                                          \
            std::source_location loc = std::source_location::current()                             \
        ) {                                                                                        \
            detail::logger(Level::LEVEL, std::move(message), loc);                                 \
        }                                                                                          \
                                                                                                   \
        constexpr explicit level(                                                                  \
            std::format_string<Args...> fmt,                                                       \
            Args&&... args,                                                                        \
            std::source_location loc = std::source_location::current()                             \
        )                                                                                          \
            : level(std::vformat(fmt.get(), std::make_format_args(args...)), loc) {}               \
    };                                                                                             \
                                                                                                   \
    template<typename... Args>                                                                     \
    level(Args&&...) -> level<Args...>;                                                            \
    template<typename... Args>                                                                     \
    level(const char*) -> level<std::string>;                                                      \
    template<typename... Args>                                                                     \
    level(const char*, Args&&...) -> level<Args...>;

RG_LOG_STRUCT(trace, TRACE)
RG_LOG_STRUCT(debug, DEBUG)
RG_LOG_STRUCT(info, INFO)
RG_LOG_STRUCT(note, NOTE)
RG_LOG_STRUCT(progress, PROGRESS)
RG_LOG_STRUCT(warning, WARNING)
RG_LOG_STRUCT(error, ERROR)
RG_LOG_STRUCT(fatal, FATAL)

#undef RG_LOG_STRUCT
} // namespace core::log
