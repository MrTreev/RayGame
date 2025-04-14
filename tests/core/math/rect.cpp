#include "raygame/core/math/rect.h"
#include "raygame/core/test/tests_begin.h"

TEST_SUITE("core::Rect") {
    using core::Rect;
    using core::Vec2;
    TEST_CASE_TEMPLATE("Constructors", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
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
        CHECK_EQ(test_rec_0, test_rec_1);
        CHECK_EQ(test_rec_1, test_rec_2);
        CHECK_EQ(test_rec_3, test_rec_4);
    }
    TEST_CASE_TEMPLATE("set with pos", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
        Rect<pos_t, dis_t> test_rec{};
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({0, 0}, {0, 0}));
        test_rec.pos(1, 2);
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({1, 2}, {0, 0}));
        test_rec.pos(Vec2<pos_t>(3, 4));
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({3, 4}, {0, 0}));
    }
    TEST_CASE_TEMPLATE("set with zero", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
        const Rect<pos_t, dis_t> test_rec{};
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({0, 0}, {0, 0}));
        Rect<pos_t, dis_t> test_other{
            {1, 1},
            {2, 2}
        };
        test_other.zero();
        CHECK_EQ(test_other, test_rec);
    }
    TEST_CASE_TEMPLATE("set with size", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
        Rect<pos_t, dis_t> test_rec{};
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({0, 0}, {0, 0}));
        test_rec.size(1, 2);
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({0, 0}, {1, 2}));
        test_rec.size(Vec2<pos_t>(3, 4));
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({0, 0}, {3, 4}));
        test_rec.zero();
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({0, 0}, {0, 0}));
    }
    TEST_CASE_TEMPLATE("Getters", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
        const Rect<pos_t, dis_t> test_rec{
            {1, 2},
            {3, 4}
        };
        CHECK_EQ(test_rec.pos(), Vec2<pos_t>(1, 2));
        CHECK_EQ(test_rec.size(), Vec2<dis_t>(3, 4));
        const std::string test_str  = std::string(test_rec);
        const std::string check_str = "Rect(x: 1, y: 2, width: 3, height: 4)";
        CHECK_EQ(test_str, check_str);
    }
    TEST_CASE_TEMPLATE("Scalers", T, FWINT_PAIRS) {
        using pos_t = T::A;
        using dis_t = T::B;
        Rect<pos_t, dis_t> test_rec{};
        test_rec.scale_add(Vec2<pos_t>(1, 2));
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({0, 0}, {1, 2}));
        test_rec.scale_add(1, 2);
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({0, 0}, {2, 4}));
        test_rec.zero();
        CHECK_EQ(test_rec, Rect<pos_t, dis_t>({0, 0}, {0, 0}));
    }
}
