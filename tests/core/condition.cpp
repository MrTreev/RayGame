#include "raygame/core/condition.h" // IWYU pragma: keep
#include "raygame/core/exception.h"
#include "raytest/tests_begin.h"

TEST_CASE("core::condition") {
    SUBCASE("pre_condition") {
        using core::condition::pre_condition;
        using core::exception::PreCondition;
        CHECK_NOTHROW(pre_condition(true, "true"));
        CHECK_THROWS_AS(pre_condition(false, "false"), PreCondition);
    }
    SUBCASE("post_condition") {
        using core::condition::post_condition;
        using core::exception::PostCondition;
        CHECK_NOTHROW(post_condition(true, "true"));
        CHECK_THROWS_AS(post_condition(false, "false"), PostCondition);
    }
    SUBCASE("check_condition") {
        using core::condition::check_condition;
        using core::exception::CheckCondition;
        CHECK_NOTHROW(check_condition(true, "true"));
        CHECK_THROWS_AS(check_condition(false, "false"), CheckCondition);
    }
}

TEST_CASE_TEMPLATE("core::condition check in-range", T, FWINTS) {
    using core::condition::check_ptr;
    using core::exception::CheckCondition;
    const T* tst_null = nullptr;
    const T  tst_val  = 1;
    const T* tst      = &tst_val;
    CHECK_NOTHROW(check_ptr(tst, "non-null"));
    CHECK_THROWS_AS(check_ptr(tst_null, "null"), CheckCondition);
}
