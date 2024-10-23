#include "core/math/arithmetic/safe_add.h" // IWYU pragma: keep

#if defined(RAYGAME_ENABLE_TESTS)
#    include "test/tests_begin.h"

TEST_SUITE("core::math::safe_add") {
    using core::math::safe_add;
    using core::math::MathRule::ALLOW;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    using test::max;
    TEST_CASE_TEMPLATE("in-range", T, FWINTS) {
        const T a = 0;
        const T b = 1;
        CHECK_EQ(safe_add<T, STRICT>(a, b), 1);
        CHECK_EQ(safe_add<T, STRICT>(max<T>() - b, b), max<T>());
        CHECK_EQ(safe_add<T, CLAMP>(a, b), 1);
        CHECK_EQ(safe_add<T, ALLOW>(a, b), 1);
    }
    TEST_CASE_TEMPLATE("out-of-range", T, FWINTS) {
        const T one = 1;
        CHECK_THROWS(safe_add<T, STRICT>(max<T>(), max<T>()));
        CHECK_NOTHROW(safe_add<T, ALLOW>(max<T>(), max<T>()));
        CHECK_EQ(safe_add<T, CLAMP>(max<T>(), max<T>()), max<T>());
        CHECK_EQ(safe_add<T, CLAMP>(max<T>(), one), max<T>());
    }
}
#endif
