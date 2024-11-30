#include "core/math/numeric_cast.h"
#include "test/tests_begin.h"

TEST_SUITE("core::math::numeric_cast") {
    using core::math::numeric_cast;
    using core::math::MathRule::STRICT;
    using test::lowest;
    using test::max;
    using test::min;
    TEST_CASE_TEMPLATE("Strict in-range does not throw", T, FWINTS) {
        CHECK_NOTHROW(numeric_cast<T, STRICT>(max<T>()));
        CHECK_NOTHROW(numeric_cast<T, STRICT>(min<T>()));
        CHECK_NOTHROW(numeric_cast<T, STRICT>(lowest<T>()));
    }
    TEST_CASE_TEMPLATE("Strict out-of-range throws", T, FWINTS) {
        CHECK_THROWS(numeric_cast<T, STRICT>(max<T>() + 1));
        CHECK_THROWS(numeric_cast<T, STRICT>(min<T>() - 1));
    }
}
