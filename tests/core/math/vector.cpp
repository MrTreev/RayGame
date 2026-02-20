#include "raygame/core/math/vector.h"
#include "raytest/raytest.h"

template<typename T>
class VectorTest: public ::testing::Test {
public:
    T val() { return 1; }
};

RT_TYPED_TEST_SUITE(VectorTest, test::types::Integral);

template<typename T>
class VectorPaired: public ::testing::Test {
public:
    T::A aval() { return 1; }

    T::B bval() { return 1; }
};

RT_TYPED_TEST_SUITE(VectorPaired, test::types::IntegralPairs);

using core::Vec2;

RT_TYPED_TEST(VectorTest, Constructors) {
    using T = decltype(this->val());
    const core::Vec2<T> test_vec0{};
    const core::Vec2<T> test_vec1{0, 0};
    RT_CHECK_EQ(test_vec0, test_vec1);
}

RT_TYPED_TEST(VectorTest, String) {
    using T = decltype(this->val());
    const core::Vec2<T> test_vec0{1, 2};
    const std::string   test_str  = std::string(test_vec0);
    const std::string   check_str = "Vec2(x: 1, y: 2)";
    RT_CHECK_EQ(test_str, check_str);
}

RT_TYPED_TEST(VectorPaired, Equality) {
    using a_t = decltype(this->aval());
    using b_t = decltype(this->bval());
    const core::Vec2<a_t> test_vec0{1, 2};
    const core::Vec2<a_t> test_vec1{1, 2};
    const core::Vec2<b_t> test_vec2{1, 2};
    RT_CHECK_EQ(test_vec0, test_vec1);
    RT_CHECK_EQ(test_vec0, test_vec2);
}

RT_TYPED_TEST(VectorPaired, Adding) {
    using a_t = decltype(this->aval());
    using b_t = decltype(this->bval());
    core::Vec2<a_t> test_vec0{1, 2};
    core::Vec2<b_t> test_vec1{3, 4};
    RT_CHECK_EQ(Vec2<a_t>(4, 6), test_vec0 + test_vec1);
    RT_CHECK_EQ(Vec2<b_t>(4, 6), test_vec0 + test_vec1);
    RT_CHECK_EQ(Vec2<b_t>(3, 4), test_vec0 + 2);
    RT_CHECK_EQ(Vec2<a_t>(5, 6), test_vec1 + 2);
    test_vec0 += test_vec1;
    test_vec1 += 2;
    RT_CHECK_EQ(Vec2<a_t>(4, 6), test_vec0);
    RT_CHECK_EQ(Vec2<a_t>(5, 6), test_vec1);
}
