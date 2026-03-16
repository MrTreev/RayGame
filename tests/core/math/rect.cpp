#include "raygame/core/math/rect.h"
#include "raytest/raytest.h"

using core::Rect;
using core::Vec2;

template<typename T>
class RectTest: public ::testing::Test {
public:
    T::A aval() { return 1; }

    T::B bval() { return 1; }
};

RT_TYPED_TEST_SUITE(RectTest, test::types::IntegralPairs);

RT_TYPED_TEST(RectTest, Constructors) {}

RT_TYPED_TEST(RectTest, SetSize) {}

RT_TYPED_TEST(RectTest, Getters) {}

RT_TYPED_TEST(RectTest, Scales) {}
