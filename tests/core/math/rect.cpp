#include "raygame/core/math/rect.hpp"
#include "raytest/raytest.hpp"

namespace {
using core::Rect;
using core::Vec2;
using core::math::MathRule::ALLOW;
using core::math::MathRule::CLAMP;
using core::math::MathRule::STRICT;
using test::max;

template<typename T>
class RectTest: public ::testing::Test {
public:
    T::A aval() { return 1; }

    T::B bval() { return 1; }
};
} // namespace

RT_TYPED_TEST_SUITE(RectTest, test::types::IntegralPairs);

RT_TYPED_TEST(RectTest, Constructors) {
    using a_t = decltype(this->aval());
    const Rect<a_t> rec0{};
    const Rect<a_t> rec1{
        Vec2<a_t>{0, 0}
    };
    RT_CHECK_EQ(rec0, rec1);
    RT_CHECK_EQ(rec0.width(), 0);
    RT_CHECK_EQ(rec0.height(), 0);
}

RT_TYPED_TEST(RectTest, SetSize) {
    using a_t = decltype(this->aval());
    using b_t = decltype(this->bval());
    Rect<a_t> rec{};
    rec.size(3, 4);
    RT_CHECK_EQ(rec.width(), 3);
    RT_CHECK_EQ(rec.height(), 4);
    rec.size(Vec2<b_t>{5, 6});
    RT_CHECK_EQ(rec.width(), 5);
    RT_CHECK_EQ(rec.height(), 6);
    rec.zero();
    RT_CHECK_EQ(rec.width(), 0);
    RT_CHECK_EQ(rec.height(), 0);
}

RT_TYPED_TEST(RectTest, Getters) {
    using a_t = decltype(this->aval());
    const Rect<a_t> rec{
        Vec2<a_t>{7, 8}
    };
    RT_CHECK_EQ(rec.width(), 7);
    RT_CHECK_EQ(rec.height(), 8);
    RT_CHECK_EQ(rec.size(), (Vec2<a_t>{7, 8}));
    RT_CHECK_EQ(std::string(rec), "Rect(width: 7, height: 8)");
}

RT_TYPED_TEST(RectTest, Scales) {
    using a_t = decltype(this->aval());
    using b_t = decltype(this->bval());
    const Vec2<a_t> vec0{2, 3};
    Rect<a_t>       rec{vec0};
    {
        rec.scale_add(1, 1);
        const Vec2<a_t> vec{3, 4};
        RT_CHECK_EQ(rec, (Rect<a_t>{vec}));
    }
    {
        rec.scale_add(Vec2<b_t>{2, 1});
        const Vec2<a_t> vec{5, 5};
        RT_CHECK_EQ(rec, (Rect<a_t>{vec}));
    }
    {
        rec.scale_mult(2, 3);
        const Vec2<a_t> vec{10, 15};
        RT_CHECK_EQ(rec, (Rect<a_t>{vec}));
    }
    {
        rec.scale_mult(Vec2<b_t>{2, 2});
        const Vec2<a_t> vec{20, 30};
        RT_CHECK_EQ(rec, (Rect<a_t>{vec}));
    }
    {
        rec.scale_mult(2);
        const Vec2<a_t> vec{40, 60};
        RT_CHECK_EQ(rec, (Rect<a_t>{vec}));
    }
}

RT_TYPED_TEST(RectTest, ScalesOutOfRange) {
    using a_t   = decltype(this->aval());
    using exp_t = core::exception::Condition;
    Vec2<a_t> vec{max<a_t>(), max<a_t>()};
    Rect<a_t> rec{vec};
    RT_CHECK_THROW((rec.template scale_add<STRICT>(1, 1)), exp_t);
    RT_CHECK_NO_THROW((rec.template scale_add<ALLOW>(1, 1)));
    rec = Rect<a_t>{
        Vec2<a_t>{max<a_t>(), max<a_t>()}
    };
    rec.template scale_add<CLAMP>(1, 1);
    RT_CHECK_EQ(rec.width(), max<a_t>());
    RT_CHECK_EQ(rec.height(), max<a_t>());
    vec = Vec2<a_t>{max<a_t>() / 2, max<a_t>() / 2};
    rec = Rect<a_t>{vec};
    RT_CHECK_THROW((rec.template scale_mult<STRICT>(3, 3)), exp_t);
    RT_CHECK_NO_THROW((rec.template scale_mult<ALLOW>(3, 3)));
}
