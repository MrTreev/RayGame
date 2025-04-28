#include "raygame/core/math/arithmetic.h"
#include "raytest/raytest.h"

template<typename T>
class ArithmeticTest: public ::testing::Test {
public:
    T val() { return 1; }
};

RG_TYPED_TEST_SUITE(ArithmeticTest, test::types::Integral);

template<typename T>
class ArithmeticPaired: public ::testing::Test {
public:
    T::A aval() { return 1; }

    T::B bval() { return 1; }
};

RG_TYPED_TEST_SUITE(ArithmeticPaired, test::types::IntegralPairs);

using exp_t = core::exception::Condition;
using core::math::safe_add;
using core::math::safe_div;
using core::math::safe_mult;
using core::math::safe_sub;
using core::math::MathRule::ALLOW;
using core::math::MathRule::CLAMP;
using core::math::MathRule::STRICT;
using test::lowest;
using test::max;
using test::min;

RG_TYPED_TEST(ArithmeticPaired, AddInRange) {
    const auto aval{this->aval()};
    const auto bval{this->bval()};
    using a_t = decltype(aval);

    RG_CHECK_EQ((safe_add<a_t, STRICT>(max<a_t>() - aval, aval)), max<a_t>());
    RG_CHECK_EQ((safe_add<a_t, STRICT>(max<a_t>() - aval, bval)), max<a_t>());
    RG_CHECK_EQ((safe_add<a_t, CLAMP>(max<a_t>() - aval, aval)), max<a_t>());
    RG_CHECK_EQ((safe_add<a_t, CLAMP>(max<a_t>() - aval, bval)), max<a_t>());
    RG_CHECK_EQ((safe_add<a_t, ALLOW>(max<a_t>() - aval, aval)), max<a_t>());
    RG_CHECK_EQ((safe_add<a_t, ALLOW>(max<a_t>() - aval, bval)), max<a_t>());
    RG_CHECK_EQ((safe_add<a_t, STRICT>(aval, bval)), 2);
    RG_CHECK_EQ((safe_add<a_t, CLAMP>(aval, bval)), 2);
    RG_CHECK_EQ((safe_add<a_t, ALLOW>(aval, bval)), 2);
}

RG_TYPED_TEST(ArithmeticPaired, AddOutOfRange) {
    using a_t = decltype(this->aval());
    using b_t = decltype(this->bval());
    const b_t val{1};
    RG_CHECK_THROW((safe_add<a_t, STRICT>(max<a_t>(), val)), exp_t);
    RG_CHECK_NO_THROW((safe_add<a_t, ALLOW>(max<a_t>(), val)));
    RG_CHECK_EQ((safe_add<a_t, CLAMP>(max<a_t>(), val)), max<a_t>());
    RG_CHECK_EQ((safe_add<a_t, CLAMP>(lowest<a_t>(), -1)), lowest<a_t>());
}

RG_TYPED_TEST(ArithmeticPaired, SubInRange) {
    using a_t     = decltype(this->aval());
    using b_t     = decltype(this->bval());
    const a_t a   = 2; // NOLINT(*-identifier-length)
    const b_t b   = 1; // NOLINT(*-identifier-length)
    const a_t sub = 1;
    RG_CHECK_EQ((safe_sub<a_t, STRICT>(lowest<a_t>() + a, a)), lowest<a_t>());
    RG_CHECK_EQ((safe_sub<a_t, STRICT>(lowest<a_t>() + sub, b)), lowest<a_t>());
    RG_CHECK_EQ((safe_sub<a_t, STRICT>(a, b)), 1);
    RG_CHECK_EQ((safe_sub<a_t, CLAMP>(a, b)), 1);
    RG_CHECK_EQ((safe_sub<a_t, ALLOW>(a, b)), 1);
}

RG_TYPED_TEST(ArithmeticPaired, SubOutOfRange) {
    using a_t     = decltype(this->aval());
    using b_t     = decltype(this->bval());
    const b_t sub = 1;
    RG_CHECK_THROW((safe_sub<a_t, STRICT>(lowest<a_t>(), sub)), exp_t);
    RG_CHECK_NO_THROW((safe_sub<a_t, ALLOW>(lowest<a_t>(), sub)));
    RG_CHECK_EQ((safe_sub<a_t, CLAMP>(lowest<a_t>(), sub)), lowest<a_t>());
    RG_CHECK_EQ((safe_sub<a_t, CLAMP>(max<a_t>(), -1)), max<a_t>());
}

RG_TYPED_TEST(ArithmeticTest, DivInRange) {
    using T      = decltype(this->val());
    const T two  = 2;
    const T one  = 1;
    const T zero = 0;

    RG_CHECK_EQ((safe_div<T, STRICT>(zero, two)), zero);
    RG_CHECK_EQ((safe_div<T, CLAMP>(zero, two)), zero);
    RG_CHECK_EQ((safe_div<T, ALLOW>(zero, two)), zero);

    RG_CHECK_EQ((safe_div<T, STRICT>(two, one)), two);
    RG_CHECK_EQ((safe_div<T, CLAMP>(two, one)), two);
    RG_CHECK_EQ((safe_div<T, ALLOW>(two, one)), two);
}

RG_TYPED_TEST(ArithmeticTest, DivOutOfRange) {
    using T      = decltype(this->val());
    const T two  = 2;
    const T zero = 0;
    RG_CHECK_THROW((safe_div<T, STRICT>(two, zero)), exp_t);
    RG_CHECK_THROW((safe_div<T, CLAMP>(two, zero)), exp_t);
    RG_CHECK_THROW((safe_div<T, ALLOW>(two, zero)), exp_t);
    RG_CHECK_THROW((safe_div<T, STRICT>(zero, zero)), exp_t);
    RG_CHECK_THROW((safe_div<T, CLAMP>(zero, zero)), exp_t);
    RG_CHECK_THROW((safe_div<T, ALLOW>(zero, zero)), exp_t);
    const std::make_signed_t<T> sub = -1;
    RG_CHECK_THROW((safe_div<T, STRICT>(min<T>(), sub)), exp_t);
    if constexpr (!std::is_same_v<T, long>) {
        RG_CHECK_NO_THROW((safe_div<T, ALLOW>(min<T>(), sub)));
    }
    RG_CHECK_EQ((safe_div<T, CLAMP>(min<T>(), sub)), max<T>());
    RG_CHECK_EQ((safe_div<T, CLAMP>(min<T>(), sub)), max<T>());
}

RG_TYPED_TEST(ArithmeticTest, MultInRange) {
    using T      = decltype(this->val());
    // NOLINTBEGIN(*-identifier-length)
    const T a    = 2;
    const T b    = 2;
    const T c    = 4;
    // NOLINTEND(*-identifier-length)
    const T one  = 1;
    const T zero = 0;

    RG_CHECK_EQ((safe_mult<T, STRICT>(a, one)), (safe_mult<T, STRICT>(one, a)));
    RG_CHECK_EQ((safe_mult<T, CLAMP>(a, one)), (safe_mult<T, CLAMP>(one, a)));
    RG_CHECK_EQ((safe_mult<T, ALLOW>(a, one)), (safe_mult<T, ALLOW>(one, a)));

    RG_CHECK_EQ((safe_mult<T, STRICT>(a, b)), c);
    RG_CHECK_EQ((safe_mult<T, CLAMP>(a, b)), c);
    RG_CHECK_EQ((safe_mult<T, ALLOW>(a, b)), c);

    RG_CHECK_EQ((safe_mult<T, STRICT>(a, one)), a);
    RG_CHECK_EQ((safe_mult<T, CLAMP>(a, one)), a);
    RG_CHECK_EQ((safe_mult<T, ALLOW>(a, one)), a);

    RG_CHECK_EQ((safe_mult<T, STRICT>(a, zero)), 0);
    RG_CHECK_EQ((safe_mult<T, CLAMP>(a, zero)), 0);
    RG_CHECK_EQ((safe_mult<T, ALLOW>(a, zero)), 0);
}

RG_TYPED_TEST(ArithmeticTest, MultOutOfRange) {
    using T      = decltype(this->val());
    const T mult = 3;
    RG_CHECK_THROW((safe_mult<T, STRICT>(max<T>() / 2, mult)), exp_t);
    RG_CHECK_NO_THROW((safe_mult<T, ALLOW>(max<T>() / 2, mult)));
    RG_CHECK_EQ((safe_mult<T, CLAMP>(max<T>() / 2, mult)), max<T>());
    RG_CHECK_EQ((safe_mult<T, CLAMP>(max<T>() / 2, mult)), max<T>());
}
