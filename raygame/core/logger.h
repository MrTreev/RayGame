#pragma once
#include "raygame/core/config.h"
#include <format>
#include <source_location>
#include <string>
#include <utility>

namespace core::log {
//! Logging level to string converter
namespace detail {
void logger(Level level, std::string text, std::source_location loc);
} // namespace detail

template<Level level, typename... Args>
class logstruct {
public:
    ~logstruct()                           = default;
    logstruct(const logstruct&)            = delete;
    logstruct(logstruct&&)                 = delete;
    logstruct& operator=(const logstruct&) = delete;
    logstruct& operator=(logstruct&&)      = delete;

    constexpr explicit logstruct(
        const char*          message,
        std::source_location loc = std::source_location::current()
    ) {
        detail::logger(level, message, loc);
    }

    constexpr explicit logstruct(
        std::source_location loc,
        std::string          message
    ) {
        detail::logger(level, std::move(message), loc);
    }

    constexpr explicit logstruct(
        std::format_string<Args...> fmt,
        Args&&... args,
        std::source_location loc = std::source_location::current()
    ) {
        detail::logger(
            level,
            std::format(fmt, std::forward<Args>(args)...),
            loc
        );
    }
};

// clang-format off

template<typename... Ts> class trace: public logstruct<Level::TRACE, Ts...> {};
template<typename... Ts> trace(Ts&&...) -> trace<Ts...>;
template<typename... Ts> trace(Ts&&..., const std::source_location&) -> trace<Ts...>;
template<typename... Ts> trace(const std::source_location&, std::string) -> trace<>;

template<typename... Ts> class debug: public logstruct<Level::DEBUG, Ts...> {};
template<typename... Ts> debug(Ts&&...) -> debug<Ts...>;
template<typename... Ts> debug(Ts&&..., const std::source_location&) -> debug<Ts...>;
template<typename... Ts> debug(const std::source_location&, std::string) -> debug<>;

template<typename... Ts> class info: public logstruct<Level::INFO, Ts...> {};
template<typename... Ts> info(Ts&&...) -> info<Ts...>;
template<typename... Ts> info(Ts&&..., const std::source_location&) -> info<Ts...>;
template<typename... Ts> info(const std::source_location&, std::string) -> info<>;

template<typename... Ts> class note: public logstruct<Level::NOTE, Ts...> {};
template<typename... Ts> note(Ts&&...) -> note<Ts...>;
template<typename... Ts> note(Ts&&..., const std::source_location&) -> note<Ts...>;
template<typename... Ts> note(const std::source_location&, std::string) -> note<>;

template<typename... Ts> class progress: public logstruct<Level::PROGRESS, Ts...> {};
template<typename... Ts> progress(Ts&&...) -> progress<Ts...>;
template<typename... Ts> progress(Ts&&..., const std::source_location&) -> progress<Ts...>;
template<typename... Ts> progress(const std::source_location&, std::string) -> progress<>;

template<typename... Ts> class warning: public logstruct<Level::WARNING, Ts...> {};
template<typename... Ts> warning(Ts&&...) -> warning<Ts...>;
template<typename... Ts> warning(Ts&&..., const std::source_location&) -> warning<Ts...>;
template<typename... Ts> warning(const std::source_location&, std::string) -> warning<>;

template<typename... Ts> class error: public logstruct<Level::ERROR, Ts...> {};
template<typename... Ts> error(Ts&&...) -> error<Ts...>;
template<typename... Ts> error(Ts&&..., const std::source_location&) -> error<Ts...>;
template<typename... Ts> error(const std::source_location&, std::string) -> error<>;

template<typename... Ts> class fatal: public logstruct<Level::FATAL, Ts...> {};
template<typename... Ts> fatal(Ts&&...) -> fatal<Ts...>;
template<typename... Ts> fatal(Ts&&..., const std::source_location&) -> fatal<Ts...>;
template<typename... Ts> fatal(const std::source_location&, std::string) -> fatal<>;
// clang-format on

} // namespace core::log
