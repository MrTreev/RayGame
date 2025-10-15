#pragma once
#include <format>
#include <source_location>
#include <string_view>

#if defined(RAYGAME_LOG_TRACE)
#    define RAYGAME_LOG_LEVEL TRACE
#elif defined(RAYGAME_LOG_DEBUG)
#    define RAYGAME_LOG_LEVEL DEBUG
#elif defined(RAYGAME_LOG_INFO)
#    define RAYGAME_LOG_LEVEL INFO
#elif defined(RAYGAME_LOG_WARNING)
#    define RAYGAME_LOG_LEVEL WARNING
#elif defined(RAYGAME_LOG_ERROR)
#    define RAYGAME_LOG_LEVEL ERROR
#elif defined(RAYGAME_LOG_FATAL)
#    define RAYGAME_LOG_LEVEL FATAL
#else
#    warning "No logging level set for RAYGAME, using NOTE"
constexpr Level logging_level = Level::NOTE;
#endif

namespace core::log {
//! Logging level
enum class Level : uint8_t {
    TRACE   = 0,
    DEBUG   = 10,
    INFO    = 20,
    /* 50 - 80 */
    WARNING = 80,
    ERROR   = 90,
    FATAL   = 255,
};

//! Current logging level
constexpr Level logging_level = Level::RAYGAME_LOG_LEVEL;

//! Logging level to string converter
namespace detail {
void logger(core::log::Level level, std::string_view text, std::source_location loc);
} // namespace detail

// Makes it easier to have a single definition
// NOLINTNEXTLINE(*-macro-usage)
#define RG_LOG_STRUCT(level, LEVEL)                                                                \
    template<typename... Args>                                                                     \
    struct level {                                                                                 \
        constexpr explicit level(                                                                  \
            std::string_view     message,                                                          \
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
RG_LOG_STRUCT(warning, WARNING)
RG_LOG_STRUCT(error, ERROR)
RG_LOG_STRUCT(fatal, FATAL)

#undef RG_LOG_STRUCT
} // namespace core::log
