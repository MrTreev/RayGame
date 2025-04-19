#include "raygame/core/math/numeric_cast.h"
#include "raytest/tests_begin.h"
#include <cstdint>

TEST_SUITE("core::math::numeric_cast") {
    using core::math::numeric_cast;
    using core::math::MathRule::CLAMP;
    using core::math::MathRule::STRICT;
    using test::lowest;
    using test::max;
    using test::min;
    TEST_CASE_TEMPLATE("Strict in-range does not throw", T, FWINTS) {
        CHECK_NOTHROW(numeric_cast<T, STRICT>(max<T>()));
        CHECK_NOTHROW(numeric_cast<T, STRICT>(min<T>()));
        CHECK_NOTHROW(numeric_cast<T, STRICT>(lowest<T>()));
    }
    TEST_CASE_TEMPLATE("Strict out-of-range", T, FWINTS) {
        if constexpr (sizeof(T) < sizeof(intmax_t)) {
            CHECK_THROWS(numeric_cast<T, STRICT>(max<T>() + 1));
            CHECK_THROWS(numeric_cast<T, STRICT>(min<T>() - 1));
        }
    }
    TEST_CASE_TEMPLATE("Clamp Out-of-range", T, FWINTS) {
        if constexpr (sizeof(T) < sizeof(intmax_t)) {
            CHECK_EQ(numeric_cast<T, CLAMP>(max<T>() + 1), max<T>());
            if constexpr (std::is_signed_v<T>) {
                CHECK_EQ(numeric_cast<T, CLAMP>(min<T>() - 1), min<T>());
            }
        }
    }
    TEST_CASE_TEMPLATE("Different signedness", T, FWINTS) {
        CHECK_NOTHROW(numeric_cast<T, STRICT>(1U));
        CHECK_NOTHROW(numeric_cast<T, STRICT>(1U));
        if constexpr (std::is_signed_v<T>) {
            CHECK_NOTHROW(numeric_cast<T, STRICT>(-1));
            CHECK_NOTHROW(numeric_cast<T, STRICT>(-1));
        } else {
            CHECK_THROWS(numeric_cast<T, STRICT>(-1));
            CHECK_THROWS(numeric_cast<T, STRICT>(-1));
        }
    }
}
