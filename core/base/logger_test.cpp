#include "core/base/logger.h" // IWYU pragma: keep
#include "test/tests_begin.h"

TEST_SUITE("core::log::logger") {
    TEST_CASE("trace") {
        using core::log::trace;
        const int tmp = 1;
        trace("test");
        trace(std::string{"Welp"});
        trace("{}", 1);
        trace("{}, {}", 1, tmp);
    }

    TEST_CASE("debug") {
        using core::log::debug;
        const int tmp = 1;
        debug("test");
        debug(std::string{"Welp"});
        debug("{}", 1);
        debug("{}, {}", 1, tmp);
    }

    TEST_CASE("info") {
        using core::log::info;
        const int tmp = 1;
        info("test");
        info(std::string{"Welp"});
        info("{}", 1);
        info("{}, {}", 1, tmp);
    }

    TEST_CASE("note") {
        using core::log::note;
        const int tmp = 1;
        note("test");
        note(std::string{"Welp"});
        note("{}", 1);
        note("{}, {}", 1, tmp);
    }

    TEST_CASE("progress") {
        using core::log::progress;
        const int tmp = 1;
        progress("test");
        progress(std::string{"Welp"});
        progress("{}", 1);
        progress("{}, {}", 1, tmp);
    }

    TEST_CASE("warning") {
        using core::log::warning;
        const int tmp = 1;
        warning("test");
        warning(std::string{"Welp"});
        warning("{}", 1);
        warning("{}, {}", 1, tmp);
    }

    TEST_CASE("error") {
        using core::log::error;
        const int tmp = 1;
        error("test");
        error(std::string{"Welp"});
        error("{}", 1);
        error("{}, {}", 1, tmp);
    }

    TEST_CASE("fatal") {
        using core::log::fatal;
        const int tmp = 1;
        fatal("test");
        fatal(std::string{"Welp"});
        fatal("{}", 1);
        fatal("{}, {}", 1, tmp);
    }
}
