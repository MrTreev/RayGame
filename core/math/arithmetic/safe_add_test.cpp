#include "core/math/arithmetic/safe_add.h"
#include "test/tests_begin.h"

TEST_SUITE("core::math::safe_add") {
    using core::math::safe_add;
    using core::math::MathRule::ALLOW;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    using test::max;
    TEST_CASE_TEMPLATE("in-range", T, FWINT_PAIRS) {
        using a_t   = T::A;
        using b_t   = T::B;
        const a_t a = 1;
        const b_t b = 1;
        CHECK_EQ(safe_add<a_t, STRICT>(max<a_t>() - a, a), max<a_t>());
        CHECK_EQ(safe_add<a_t, STRICT>(max<a_t>() - b, b), max<a_t>());
        CHECK_EQ(safe_add<a_t, CLAMP>(max<a_t>() - a, a), max<a_t>());
        CHECK_EQ(safe_add<a_t, CLAMP>(max<a_t>() - b, b), max<a_t>());
        CHECK_EQ(safe_add<a_t, ALLOW>(max<a_t>() - a, a), max<a_t>());
        CHECK_EQ(safe_add<a_t, ALLOW>(max<a_t>() - b, b), max<a_t>());
        CHECK_EQ(safe_add<a_t, STRICT>(a, b), 2);
        CHECK_EQ(safe_add<a_t, CLAMP>(a, b), 2);
        CHECK_EQ(safe_add<a_t, ALLOW>(a, b), 2);
    }
    TEST_CASE_TEMPLATE("out-of-range", T, FWINT_PAIRS) {
        using a_t     = T::A;
        using b_t     = T::B;
        const b_t val = 1;
        CHECK_THROWS(safe_add<a_t, STRICT>(max<a_t>(), val));
        CHECK_NOTHROW(safe_add<a_t, ALLOW>(max<a_t>(), val));
        CHECK_EQ(safe_add<a_t, CLAMP>(max<a_t>(), val), max<a_t>());
    }
}
