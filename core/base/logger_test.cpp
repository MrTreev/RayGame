#include "core/base/logger.h" // IWYU pragma: keep
#include "test/tests_begin.h"

TEST_SUITE("core::log::logger") {
    using core::log::debug;
    TEST_CASE("debug") {
        debug("test");
        debug(std::format("{}", 1));
        // debug("{}", 1);
    }
}
