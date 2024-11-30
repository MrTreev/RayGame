#include "core/math/arithmetic/safe_sub.h" // IWYU pragma: keep
#include "test/tests_begin.h"

TEST_SUITE("core::math::safe_sub") {
    using core::math::safe_sub;
    using core::math::MathRule::ALLOW;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    TEST_CASE_TEMPLATE("in-range", T, FWINT_PAIRS) {
        using a_t   = T::A;
        using b_t   = T::B;
        const a_t a = 2;
        const b_t b = 1;
        CHECK_EQ(
            safe_sub<a_t, STRICT>(test::lowest<a_t>() + a, a),
            test::lowest<a_t>()
        );
        CHECK_EQ(
            safe_sub<a_t, STRICT>(
                test::lowest<a_t>() + core::math::numeric_cast<a_t>(b),
                b
            ),
            test::lowest<a_t>()
        );
        CHECK_EQ(safe_sub<a_t, STRICT>(a, b), 1);
        CHECK_EQ(safe_sub<a_t, CLAMP>(a, b), 1);
        CHECK_EQ(safe_sub<a_t, ALLOW>(a, b), 1);
    }
    TEST_CASE_TEMPLATE("out-of-range", T, FWINT_PAIRS) {
        using a_t     = T::A;
        using b_t     = T::B;
        const b_t sub = 1;
        CHECK_THROWS(safe_sub<a_t, STRICT>(test::lowest<a_t>(), sub));
        CHECK_NOTHROW(safe_sub<a_t, ALLOW>(test::lowest<a_t>(), sub));
        CHECK_EQ(
            safe_sub<a_t, CLAMP>(test::lowest<a_t>(), sub),
            test::lowest<a_t>()
        );
    }
}
