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

RT_TYPED_TEST_SUITE(NumericCast, test::types::Integral);

RT_TYPED_TEST(NumericCast, Strict) {
    using T = decltype(this->val());
    RT_CHECK_NO_THROW((numeric_cast<T, STRICT>(max<T>())));
    RT_CHECK_NO_THROW((numeric_cast<T, STRICT>(min<T>())));
    RT_CHECK_NO_THROW((numeric_cast<T, STRICT>(lowest<T>())));
    if constexpr (sizeof(T) < sizeof(intmax_t)) {
        RT_CHECK_THROW((numeric_cast<T, STRICT>(max<T>() + 1)), exp_t);
        RT_CHECK_THROW((numeric_cast<T, STRICT>(min<T>() - 1)), exp_t);
    }
}

RT_TYPED_TEST(NumericCast, Clamp) {
    using T = decltype(this->val());
    if constexpr (sizeof(T) < sizeof(intmax_t)) {
        RT_CHECK_EQ((numeric_cast<T, CLAMP>(max<T>() + 1)), max<T>());
        if constexpr (std::is_signed_v<T>) {
            RT_CHECK_EQ((numeric_cast<T, CLAMP>(min<T>() - 1)), min<T>());
        }
    }
}

RT_TYPED_TEST(NumericCast, Signedness) {
    using T = decltype(this->val());
    RT_CHECK_NO_THROW((numeric_cast<T, STRICT>(1U)));
    RT_CHECK_NO_THROW((numeric_cast<T, STRICT>(1U)));
    if constexpr (std::is_signed_v<T>) {
        RT_CHECK_NO_THROW((numeric_cast<T, STRICT>(-1)));
        RT_CHECK_NO_THROW((numeric_cast<T, STRICT>(-1)));
    } else {
        RT_CHECK_THROW((numeric_cast<T, STRICT>(-1)), exp_t);
        RT_CHECK_THROW((numeric_cast<T, STRICT>(-1)), exp_t);
    }
}
