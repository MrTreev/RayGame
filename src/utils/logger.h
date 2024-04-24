#pragma once
#include <string>

namespace utils {

enum class Level {
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

#if !defined(RAYGAME_LOGGING_LEVEL)
constexpr Level logging_level = Level::NOTE;
#elif (RAYGAME_LOGGING_LEVEL == TRACE)
constexpr Level logging_level = Level::TRACE;
#elif (RAYGAME_LOGGING_LEVEL == DEBUG)
constexpr Level logging_level = Level::DEBUG;
#elif (RAYGAME_LOGGING_LEVEL == INFO)
constexpr Level logging_level = Level::INFO;
#elif (RAYGAME_LOGGING_LEVEL == NOTE)
constexpr Level logging_level = Level::NOTE;
#elif (RAYGAME_LOGGING_LEVEL == PROGRESS)
constexpr Level logging_level = Level::PROGRESS;
#elif (RAYGAME_LOGGING_LEVEL == WARNING)
constexpr Level logging_level = Level::WARNING;
#elif (RAYGAME_LOGGING_LEVEL == ERROR)
constexpr Level logging_level = Level::ERROR;
#elif (RAYGAME_LOGGING_LEVEL == FATAL)
constexpr Level logging_level = Level::FATAL;
#else
#error "Bad value for RAYGAME_LOGGING_LEVEL"
#endif

std::string ToString(Level v);

template <typename T>
void logger(const Level level, const T &text);

namespace log {

template <typename T>
inline void trace(const T &text) {
    logger(Level::TRACE, text);
};

template <typename T>
inline void debug(const T &text) {
    logger(Level::DEBUG, text);
};

template <typename T>
inline void info(const T &text) {
    logger(Level::INFO, text);
};

template <typename T>
inline void note(const T &text) {
    logger(Level::NOTE, text);
};

template <typename T>
inline void progress(const T &text) {
    logger(Level::PROGRESS, text);
};

template <typename T>
inline void warning(const T &text) {
    logger(Level::WARNING, text);
};

template <typename T>
inline void error(const T &text) {
    logger(Level::ERROR, text);
};

template <typename T>
inline void fatal(const T &text) {
    logger(Level::FATAL, text);
};

} // namespace log
} // namespace utils
