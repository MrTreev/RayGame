#include "core/math/arithmetic/safe_sub.h" // IWYU pragma: keep

#if defined(RAYGAME_ENABLE_TESTS)
#    include "test/tests_begin.h"

TEST_SUITE("core::math::safe_sub") {
    using core::math::safe_sub;
    using core::math::MathRule::ALLOW;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    using test::min;
    TEST_CASE_TEMPLATE("in-range", T, FWINTS) {
        const T a = 2;
        const T b = 1;
        CHECK_EQ(safe_sub<T, STRICT>(min<T>() + a, a), min<T>());
        CHECK_EQ(safe_sub<T, STRICT>(a, b), 1);
        CHECK_EQ(safe_sub<T, CLAMP>(a, b), 1);
        CHECK_EQ(safe_sub<T, ALLOW>(a, b), 1);
    }
    TEST_CASE_TEMPLATE("out-of-range", T, FWINTS) {
        const T sub = 1;
        CHECK_THROWS(safe_sub<T, STRICT>(min<T>(), sub));
        CHECK_NOTHROW(safe_sub<T, ALLOW>(min<T>(), sub));
        CHECK_EQ(safe_sub<T, CLAMP>(min<T>(), sub), min<T>());
        CHECK_EQ(safe_sub<T, CLAMP>(min<T>(), sub), min<T>());
    }
}
#endif
