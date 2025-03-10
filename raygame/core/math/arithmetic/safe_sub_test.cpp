#include "raygame/core/math/arithmetic/safe_sub.h" // IWYU pragma: keep
#include "raygame/core/test/tests_begin.h"

TEST_SUITE("core::math::safe_sub") {
    using core::math::safe_sub;
    using core::math::MathRule::ALLOW;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    using test::lowest;
    using test::max;
    TEST_CASE_TEMPLATE("in-range", T, FWINT_PAIRS) {
        using a_t     = T::A;
        using b_t     = T::B;
        // NOLINTBEGIN(*-identifier-length)
        const a_t a   = 2;
        const b_t b   = 1;
        // NOLINTEND(*-identifier-length)
        const a_t sub = 1;
        CHECK_EQ(safe_sub<a_t, STRICT>(lowest<a_t>() + a, a), lowest<a_t>());
        CHECK_EQ(safe_sub<a_t, STRICT>(lowest<a_t>() + sub, b), lowest<a_t>());
        CHECK_EQ(safe_sub<a_t, STRICT>(a, b), 1);
        CHECK_EQ(safe_sub<a_t, CLAMP>(a, b), 1);
        CHECK_EQ(safe_sub<a_t, ALLOW>(a, b), 1);
    }
    TEST_CASE_TEMPLATE("out-of-range", T, FWINT_PAIRS) {
        using a_t     = T::A;
        using b_t     = T::B;
        const b_t sub = 1;
        CHECK_THROWS(safe_sub<a_t, STRICT>(lowest<a_t>(), sub));
        CHECK_NOTHROW(safe_sub<a_t, ALLOW>(lowest<a_t>(), sub));
        CHECK_EQ(safe_sub<a_t, CLAMP>(lowest<a_t>(), sub), lowest<a_t>());
        CHECK_EQ(safe_sub<a_t, CLAMP>(max<a_t>(), -1), max<a_t>());
    }
}
