#include "raygame/core/math/arithmetic/safe_div.h"
#include "raygame/core/test/tests_begin.h"

TEST_SUITE("core::math::safe_div") {
    using core::math::safe_div;
    using core::math::MathRule::ALLOW;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    using test::max;
    using test::min;
    TEST_CASE_TEMPLATE("in-range", T, FWINTS) {
        const T two  = 2;
        const T one  = 1;
        const T zero = 0;

        CHECK_EQ(safe_div<T, STRICT>(zero, two), zero);
        CHECK_EQ(safe_div<T, CLAMP>(zero, two), zero);
        CHECK_EQ(safe_div<T, ALLOW>(zero, two), zero);

        CHECK_EQ(safe_div<T, STRICT>(two, one), two);
        CHECK_EQ(safe_div<T, CLAMP>(two, one), two);
        CHECK_EQ(safe_div<T, ALLOW>(two, one), two);
    }
    TEST_CASE_TEMPLATE("out-of-range", T, FWINTS) {
        const T two  = 2;
        const T zero = 0;
        CHECK_THROWS(safe_div<T, STRICT>(two, zero));
        CHECK_THROWS(safe_div<T, CLAMP>(two, zero));
        CHECK_THROWS(safe_div<T, ALLOW>(two, zero));
        CHECK_THROWS(safe_div<T, STRICT>(zero, zero));
        CHECK_THROWS(safe_div<T, CLAMP>(zero, zero));
        CHECK_THROWS(safe_div<T, ALLOW>(zero, zero));
        const std::make_signed_t<T> sub = -1;
        CHECK_THROWS(safe_div<T, STRICT>(min<T>(), sub));
        if constexpr (!std::is_same_v<T, long>) {
            CHECK_NOTHROW(safe_div<T, ALLOW>(min<T>(), sub));
        }
        CHECK_EQ(safe_div<T, CLAMP>(min<T>(), sub), max<T>());
        CHECK_EQ(safe_div<T, CLAMP>(min<T>(), sub), max<T>());
    }
}
