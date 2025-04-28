#include "raygame/core/math/numeric_cast.h"
#include "raytest/raytest.h"
#include <cstdint>

using exp_t = core::exception::Condition;
using core::math::numeric_cast;
using core::math::MathRule::CLAMP;
using core::math::MathRule::STRICT;
using test::lowest;
using test::max;
using test::min;

template<typename T>
class NumericCast: public ::testing::Test {
public:
    T val() { return 1; }
};

RG_TYPED_TEST_SUITE(NumericCast, test::types::Integral);

RG_TYPED_TEST(NumericCast, Strict) {
    using T = decltype(this->val());
    RG_CHECK_NO_THROW((numeric_cast<T, STRICT>(max<T>())));
    RG_CHECK_NO_THROW((numeric_cast<T, STRICT>(min<T>())));
    RG_CHECK_NO_THROW((numeric_cast<T, STRICT>(lowest<T>())));
    if constexpr (sizeof(T) < sizeof(intmax_t)) {
        RG_CHECK_THROW((numeric_cast<T, STRICT>(max<T>() + 1)), exp_t);
        RG_CHECK_THROW((numeric_cast<T, STRICT>(min<T>() - 1)), exp_t);
    }
}

RG_TYPED_TEST(NumericCast, Clamp) {
    using T = decltype(this->val());
    if constexpr (sizeof(T) < sizeof(intmax_t)) {
        RG_CHECK_EQ((numeric_cast<T, CLAMP>(max<T>() + 1)), max<T>());
        if constexpr (std::is_signed_v<T>) {
            RG_CHECK_EQ((numeric_cast<T, CLAMP>(min<T>() - 1)), min<T>());
        }
    }
}

RG_TYPED_TEST(NumericCast, Signedness) {
    using T = decltype(this->val());
    RG_CHECK_NO_THROW((numeric_cast<T, STRICT>(1U)));
    RG_CHECK_NO_THROW((numeric_cast<T, STRICT>(1U)));
    if constexpr (std::is_signed_v<T>) {
        RG_CHECK_NO_THROW((numeric_cast<T, STRICT>(-1)));
        RG_CHECK_NO_THROW((numeric_cast<T, STRICT>(-1)));
    } else {
        RG_CHECK_THROW((numeric_cast<T, STRICT>(-1)), exp_t);
        RG_CHECK_THROW((numeric_cast<T, STRICT>(-1)), exp_t);
    }
}
