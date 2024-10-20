#include "core/math/math.h"
#include <fuzztest/fuzztest.h>
#include <gtest/gtest.h>

using core::exception::Condition;
#define S_FWINTS uint8_t, uint16_t, uint32_t
#define U_FWINTS int8_t, int16_t, int32_t
#define FWINTS   U_FWINTS, S_FWINTS

namespace rg::test {

void CoverAllRand(const intmax_t a, const intmax_t b) {
    if (a >= b) {
        EXPECT_THROW(core::math::rand(a, b), Condition);
    } else {
        const auto randno = core::math::rand(a, b);
        EXPECT_GE(randno, a);
        EXPECT_LE(randno, b);
    }
}

class FuzzMath: public testing::Test {};

using FuzzInts = ::testing::Types<FWINTS>;
TYPED_TEST_SUITE(FuzzMath, FuzzInts);
FUZZ_TEST(AllMathTest, CoverAllRand);

} // namespace rg::test
