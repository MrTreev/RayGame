#include "core/math/vector.h"
#include "test/tests_begin.h"

TEST_SUITE("core::Vec2") {
    using core::Vec2;
    TEST_CASE_TEMPLATE("Constructors", T, FWINTS) {
        core::Vec2<T> test_vec0{};
        core::Vec2<T> test_vec1{0, 0};
        CHECK_EQ(test_vec0, test_vec1);
    }
    TEST_CASE_TEMPLATE("Equality", T, FWINTS) {
        core::Vec2<T> test_vec0{1, 2};
        core::Vec2<T> test_vec1{1, 2};
        CHECK_EQ(test_vec0, test_vec1);
    }
}
