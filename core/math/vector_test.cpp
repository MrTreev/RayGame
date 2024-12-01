#include "core/math/vector.h"
#include "test/tests_begin.h"

TEST_SUITE("core::Vec2") {
    using core::Vec2;
    TEST_CASE_TEMPLATE("Constructors", T, FWINTS) {
        core::Vec2<T> test_vec0{};
        core::Vec2<T> test_vec1{0, 0};
        CHECK_EQ(test_vec0, test_vec1);
    }
    TEST_CASE_TEMPLATE("Equality", T, FWINT_PAIRS) {
        using a_t = T::A;
        using b_t = T::B;
        core::Vec2<a_t> test_vec0{1, 2};
        core::Vec2<a_t> test_vec1{1, 2};
        core::Vec2<b_t> test_vec2{1, 2};
        CHECK_EQ(test_vec0, test_vec1);
        CHECK_EQ(test_vec0, test_vec2);
    }
    TEST_CASE_TEMPLATE("Adding", T, FWINT_PAIRS) {
        using a_t = T::A;
        using b_t = T::B;
        core::Vec2<a_t> test_vec0{1, 2};
        core::Vec2<b_t> test_vec1{3, 4};
        CHECK_EQ(Vec2<a_t>(4, 6), test_vec0 + test_vec1);
        CHECK_EQ(Vec2<b_t>(4, 6), test_vec0 + test_vec1);
        CHECK_EQ(Vec2<b_t>(3, 4), test_vec0 + 2);
        CHECK_EQ(Vec2<a_t>(5, 6), test_vec1 + 2);
        test_vec0 += test_vec1;
        test_vec1 += 2;
        CHECK_EQ(Vec2<a_t>(4, 6), test_vec0);
        CHECK_EQ(Vec2<a_t>(5, 6), test_vec1);
    }
    TEST_CASE_TEMPLATE("String", T, FWINTS) {
        core::Vec2<T>     test_vec0{1, 2};
        const std::string test_str  = std::string(test_vec0);
        const std::string check_str = "Vec2(x: 1, y: 2)";
        CHECK_EQ(test_str, check_str);
    }
}
