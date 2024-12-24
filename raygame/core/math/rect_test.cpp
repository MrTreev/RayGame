#include "raygame/core/math/rect.h"
#include "raygame/core/test/tests_begin.h"

TEST_SUITE("core::Rect") {
    using core::Rect;
    using core::Vec2;
    TEST_CASE_TEMPLATE("Constructors", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
        Rect<pos_t, dis_t> test_rec_0{0, 0, 0, 0};
        Rect<pos_t, dis_t> test_rec_1{};
        Rect<pos_t, dis_t> test_rec_2{{}, {}};
        Rect<pos_t, dis_t> test_rec_3{0, 1, 2, 3};
        Rect<pos_t, dis_t> test_rec_4{
            {0, 1},
            {2, 3}
        };
        Vec2<pos_t>        posvec{1, 2};
        Vec2<dis_t>        disvec{3, 4};
        Rect<pos_t, dis_t> test_rec_5{posvec, disvec};
        Rect<pos_t, dis_t> test_rec_6{1, 2, 3, 4};
        CHECK_EQ(test_rec_0, test_rec_1);
        CHECK_EQ(test_rec_1, test_rec_2);
        CHECK_EQ(test_rec_3, test_rec_4);
        CHECK_EQ(test_rec_5, test_rec_6);
    }
    TEST_CASE_TEMPLATE("Setters", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
        Rect<pos_t, dis_t> test_rec{0, 0, 0, 0};
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(0, 0, 0, 0));
        test_rec.pos(1, 2);
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(1, 2, 0, 0));
        test_rec.pos(Vec2<pos_t>(3, 4));
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(3, 4, 0, 0));
        test_rec.zero();
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(0, 0, 0, 0));
        test_rec.size(1, 2);
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(0, 0, 1, 2));
        test_rec.size(Vec2<pos_t>(3, 4));
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(0, 0, 3, 4));
        test_rec.zero();
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(0, 0, 0, 0));
    }
    TEST_CASE_TEMPLATE("Getters", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
        const Rect<pos_t, dis_t> test_rec{1, 2, 3, 4};
        CHECK_EQ(test_rec.pos(), Vec2<pos_t>(1, 2));
        CHECK_EQ(test_rec.size(), Vec2<dis_t>(3, 4));
        const std::string test_str  = std::string(test_rec);
        const std::string check_str = "Rect(x: 1, y: 2, width: 3, height: 4)";
        CHECK_EQ(test_str, check_str);
    }
    TEST_CASE_TEMPLATE("Scalers", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
        Rect<pos_t, dis_t> test_rec{0, 0, 0, 0};
        test_rec.scale_add(Vec2<pos_t>(1, 2));
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(0, 0, 1, 2));
        test_rec.scale_add(1, 2);
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(0, 0, 2, 4));
        test_rec.zero();
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>(0, 0, 0, 0));
    }
}
