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

RT_TYPED_TEST(RectTest, Constructors) {
    using pos_t = decltype(this->aval());
    using dis_t = decltype(this->bval());
    const Rect<pos_t, dis_t> test_rec_0{
        {0, 0},
        {0, 0}
    };
    const Rect<pos_t, dis_t> test_rec_1{};
    const Rect<pos_t, dis_t> test_rec_2{{}, {}};
    const Vec2<pos_t>        posvec{1, 2};
    const Vec2<dis_t>        disvec{3, 4};
    const Rect<pos_t, dis_t> test_rec_3{posvec, disvec};
    const Rect<pos_t, dis_t> test_rec_4{
        {1, 2},
        {3, 4}
    };
    RT_CHECK_EQ(test_rec_0, test_rec_1);
    RT_CHECK_EQ(test_rec_1, test_rec_2);
    RT_CHECK_EQ(test_rec_3, test_rec_4);
}

RT_TYPED_TEST(RectTest, SetPos) {
    using pos_t = decltype(this->aval());
    using dis_t = decltype(this->bval());
    Rect<pos_t, dis_t> test_rec{};
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({0, 0}, {0, 0})));
    test_rec.pos(1, 2);
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({1, 2}, {0, 0})));
    test_rec.pos(Vec2<pos_t>(3, 4));
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({3, 4}, {0, 0})));
}

RT_TYPED_TEST(RectTest, SetZero) {
    using pos_t = decltype(this->aval());
    using dis_t = decltype(this->bval());
    const Rect<pos_t, dis_t> test_rec{};
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({0, 0}, {0, 0})));
    Rect<pos_t, dis_t> test_other{
        {1, 1},
        {2, 2}
    };
    test_other.zero();
    RT_CHECK_EQ(test_other, test_rec);
}

RT_TYPED_TEST(RectTest, SetSize) {
    using pos_t = decltype(this->aval());
    using dis_t = decltype(this->bval());
    Rect<pos_t, dis_t> test_rec{};
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({0, 0}, {0, 0})));
    test_rec.size(1, 2);
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({0, 0}, {1, 2})));
    test_rec.size(Vec2<pos_t>(3, 4));
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({0, 0}, {3, 4})));
    test_rec.zero();
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({0, 0}, {0, 0})));
}

RT_TYPED_TEST(RectTest, Getters) {
    using pos_t = decltype(this->aval());
    using dis_t = decltype(this->bval());
    const Rect<pos_t, dis_t> test_rec{
        {1, 2},
        {3, 4}
    };
    RT_CHECK_EQ(test_rec.pos(), Vec2<pos_t>(1, 2));
    RT_CHECK_EQ(test_rec.size(), Vec2<dis_t>(3, 4));
    const std::string test_str  = std::string(test_rec);
    const std::string check_str = "Rect(x: 1, y: 2, width: 3, height: 4)";
    RT_CHECK_EQ(test_str, check_str);
}

RT_TYPED_TEST(RectTest, Scales) {
    using pos_t = decltype(this->aval());
    using dis_t = decltype(this->bval());
    Rect<pos_t, dis_t> test_rec{};
    test_rec.scale_add(Vec2<pos_t>(1, 2));
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({0, 0}, {1, 2})));
    test_rec.scale_add(1, 2);
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({0, 0}, {2, 4})));
    test_rec.zero();
    RT_CHECK_EQ(test_rec, (Rect<pos_t, dis_t>({0, 0}, {0, 0})));
}
