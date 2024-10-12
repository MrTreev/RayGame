#include "core/math.h"
#include "core/math/arithmetic.h"
#include "core/math/random.h"
#include "core/types.h"
#include "test/test.h"
#include <doctest/doctest.h>
#include <type_traits>

#define S_FWINTS uint8_t, uint16_t, uint32_t
#define U_FWINTS int8_t, int16_t, int32_t
#define FWINTS   U_FWINTS, S_FWINTS

using core::math::MathRule::ALLOW;
using core::math::MathRule::CLAMP;
using core::math::MathRule::STRICT;

using test::lowest;
using test::max;
using test::min;

TEST_SUITE("core::math::rand_n") {
    using core::math::rand_n;
    using test::all_same;
    constexpr size_t test_len = 16;
    TEST_CASE_TEMPLATE("std::array", T, FWINTS) {
        const T max_rand = 1;
        const T min_rand = 0;

        std::array<T, test_len> rands = rand_n<T, test_len>();
        CHECK_EQ(rands.size(), test_len);
        CHECK_FALSE(all_same(rands));
        std::array<T, test_len> rand_01 =
            rand_n<T, test_len>(min_rand, max_rand);
        CHECK_EQ(rand_01.size(), test_len);
        CHECK_FALSE(all_same(rand_01));
        for (const auto& val: rand_01) {
            CHECK_GE(val, min_rand);
            CHECK_LE(val, max_rand);
        }
    }
    TEST_CASE_TEMPLATE("std::vector", T, FWINTS) {
        const T max_rand = 1;
        const T min_rand = 0;

        std::vector<T> rands = rand_n<T>(test_len);
        CHECK_EQ(rands.size(), test_len);
        CHECK_FALSE(all_same(rands));
        std::vector<T> rand_01 = rand_n<T>(test_len, min_rand, max_rand);
        CHECK_EQ(rand_01.size(), test_len);
        CHECK_FALSE(all_same(rand_01));
        for (const auto& val: rand_01) {
            CHECK_GE(val, min_rand);
            CHECK_LE(val, max_rand);
        }
    }
}

TEST_SUITE("core::math::numeric_cast") {
    using core::math::numeric_cast;
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

TEST_SUITE("core::math::safe_add") {
    using core::math::safe_add;
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

TEST_SUITE("core::math::safe_sub") {
    using core::math::safe_sub;
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

TEST_SUITE("core::math::safe_mult") {
    using core::math::safe_mult;
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

TEST_SUITE("core::math::safe_div") {
    using core::math::safe_div;
    TEST_CASE_TEMPLATE("in-range", T, FWINTS) {
        const T a    = 2;
        const T one  = 1;
        const T zero = 0;

        CHECK_EQ(safe_div<T, STRICT>(zero, a), zero);
        CHECK_EQ(safe_div<T, CLAMP>(zero, a), zero);
        CHECK_EQ(safe_div<T, ALLOW>(zero, a), zero);

        CHECK_EQ(safe_div<T, STRICT>(a, one), a);
        CHECK_EQ(safe_div<T, CLAMP>(a, one), a);
        CHECK_EQ(safe_div<T, ALLOW>(a, one), a);
    }
    TEST_CASE_TEMPLATE("out-of-range", T, FWINTS) {
        const T a    = 2;
        const T zero = 0;
        CHECK_THROWS(safe_div<T, STRICT>(a, zero));
        CHECK_THROWS(safe_div<T, CLAMP>(a, zero));
        CHECK_THROWS(safe_div<T, ALLOW>(a, zero));
        CHECK_THROWS(safe_div<T, STRICT>(zero, zero));
        CHECK_THROWS(safe_div<T, CLAMP>(zero, zero));
        CHECK_THROWS(safe_div<T, ALLOW>(zero, zero));
        const std::make_signed_t<T> sub = -1;
        CHECK_THROWS(safe_div<T, STRICT>(min<T>(), sub));
        CHECK_NOTHROW(safe_div<T, ALLOW>(min<T>(), sub));
        CHECK_EQ(safe_div<T, CLAMP>(min<T>(), sub), max<T>());
        CHECK_EQ(safe_div<T, CLAMP>(min<T>(), sub), max<T>());
    }
}
