#pragma once
#include <cassert>
#include <sstream>
#include <string>

namespace utils {

class Logger {
    public:
        using Level = enum : char {
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

        inline const char *ToString(Level v) {
            switch (v) {
                case TRACE: return "TRACE   ";
                case DEBUG: return "DEBUG   ";
                case INFO: return "INFO    ";
                case NOTE: return "NOTE    ";
                case PROGRESS: return "PROGRESS";
                case WARNING: return "WARNING ";
                case ERROR: return "ERROR   ";
                case FATAL: return "FATAL   ";
                default: assert(false);
            }
        }

    private:
        Level level_;

    public:
        Logger(void) { level_ = INFO; };
        Logger(const Logger &c)            = delete;
        Logger &operator=(const Logger &c) = delete;

        void  set_level(Level level) { level_ = level; };
        Level get_level() { return level_; };

        void log(const Level level, const std::string &text);
        void log(const Level level, const std::ostringstream &stream);
        void log(const Level level, const char *text);
};
} // namespace utils
