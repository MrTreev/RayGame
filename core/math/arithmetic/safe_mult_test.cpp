#include "core/math/arithmetic/safe_mult.h"
#include "test/tests_begin.h"

TEST_SUITE("core::math::safe_mult") {
    using core::math::safe_mult;
    using core::math::MathRule::ALLOW;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    using test::max;
    TEST_CASE_TEMPLATE("in-range", T, FWINTS) {
        const T a    = 2;
        const T b    = 2;
        const T c    = 4;
        const T one  = 1;
        const T zero = 0;

        CHECK_EQ(safe_mult<T, STRICT>(a, one), safe_mult<T, STRICT>(one, a));
        CHECK_EQ(safe_mult<T, CLAMP>(a, one), safe_mult<T, CLAMP>(one, a));
        CHECK_EQ(safe_mult<T, ALLOW>(a, one), safe_mult<T, ALLOW>(one, a));

        CHECK_EQ(safe_mult<T, STRICT>(a, b), c);
        CHECK_EQ(safe_mult<T, CLAMP>(a, b), c);
        CHECK_EQ(safe_mult<T, ALLOW>(a, b), c);

        CHECK_EQ(safe_mult<T, STRICT>(a, one), a);
        CHECK_EQ(safe_mult<T, CLAMP>(a, one), a);
        CHECK_EQ(safe_mult<T, ALLOW>(a, one), a);

        CHECK_EQ(safe_mult<T, STRICT>(a, zero), 0);
        CHECK_EQ(safe_mult<T, CLAMP>(a, zero), 0);
        CHECK_EQ(safe_mult<T, ALLOW>(a, zero), 0);
    }
    TEST_CASE_TEMPLATE("out-of-range", T, FWINTS) {
        const T mult = 3;
        CHECK_THROWS(safe_mult<T, STRICT>(max<T>() / 2, mult));
        CHECK_NOTHROW(safe_mult<T, ALLOW>(max<T>() / 2, mult));
        CHECK_EQ(safe_mult<T, CLAMP>(max<T>() / 2, mult), max<T>());
        CHECK_EQ(safe_mult<T, CLAMP>(max<T>() / 2, mult), max<T>());
    }
}
