#pragma once
#include <string>

namespace utils
{

using Level = enum : char
{
    TRACE    = 0,
    DEBUG    = 10,
    INFO     = 20,
    NOTE     = 30,
    PROGRESS = 40,
    /* 50 - 80 */
    WARNING  = 80,
    ERROR    = 90,
    FATAL    = 100,
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
#warning "No logging level set for RAYGAME, using NOTE"
constexpr Level logging_level = Level::NOTE;
#endif

inline std::string
ToString(Level v)
{
    switch (v)
    {
        case Level::TRACE:    return "TRACE   ";
        case Level::DEBUG:    return "DEBUG   ";
        case Level::INFO:     return "INFO    ";
        case Level::NOTE:     return "NOTE    ";
        case Level::PROGRESS: return "PROGRESS";
        case Level::WARNING:  return "WARNING ";
        case Level::ERROR:    return "ERROR   ";
        case Level::FATAL:    return "FATAL   ";
        default:              static_cast<void>(v);
    }
}

void logger(const utils::Level level, std::string text);

namespace log
{

inline void
trace(std::string text)
{
    utils::logger(Level::TRACE, text);
};

inline void
debug(std::string text)
{
    utils::logger(Level::DEBUG, text);
};

inline void
info(std::string text)
{
    utils::logger(Level::INFO, text);
};

inline void
note(std::string text)
{
    utils::logger(Level::NOTE, text);
};

inline void
progress(std::string text)
{
    utils::logger(Level::PROGRESS, text);
};

inline void
warning(std::string text)
{
    utils::logger(Level::WARNING, text);
};

inline void
error(std::string text)
{
    utils::logger(Level::ERROR, text);
};

inline void
fatal(std::string text)
{
    utils::logger(Level::FATAL, text);
};

} // namespace log
} // namespace utils
