#include "core/math/arithmetic/safe_add.h"
#include "test/tests_begin.h"

TEST_SUITE("core::math::safe_add") {
    using core::math::safe_add;
    using core::math::MathRule::ALLOW;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    using test::max;
    TEST_CASE_TEMPLATE("in-range", T, FWINTS) {
        const T    a = 0;
        const T    b = 1;
        const auto c = static_cast<std::make_unsigned_t<T>>(-1);
        CHECK_EQ(safe_add<T, STRICT>(a, b), 1);
        CHECK_EQ(safe_add<T, STRICT>(max<T>() - b, b), max<T>());
        CHECK_EQ(safe_add<T, CLAMP>(a, b), 1);
        CHECK_EQ(safe_add<T, ALLOW>(a, b), 1);
        CHECK_EQ(safe_add<T, STRICT>(b, c), 0);
        CHECK_EQ(safe_add<T, STRICT>(max<T>(), c), max<T>() - 1);
        CHECK_EQ(safe_add<T, CLAMP>(b, c), 0);
        CHECK_EQ(safe_add<T, ALLOW>(b, c), 0);
    }
    TEST_CASE_TEMPLATE("out-of-range", T, FWINTS) {
        const T one = 1;
        CHECK_THROWS(safe_add<T, STRICT>(max<T>(), max<T>()));
        CHECK_NOTHROW(safe_add<T, ALLOW>(max<T>(), max<T>()));
        CHECK_EQ(safe_add<T, CLAMP>(max<T>(), max<T>()), max<T>());
        CHECK_EQ(safe_add<T, CLAMP>(max<T>(), one), max<T>());
    }
}
